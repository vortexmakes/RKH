#!/usr/bin/env python3

import collections
import sys
import subprocess
import re
import os
from email.utils import parseaddr
import logging
import argparse
from junitparser import TestCase, TestSuite, JUnitXml, Skipped, Error, Failure, Attr
import tempfile
import traceback
import magic
import shlex
from pathlib import Path
from git import Repo

logger = None

# This ends up as None when we're not running in a Zephyr tree
ZEPHYR_BASE = os.environ.get('ZEPHYR_BASE')

def git(*args, cwd=None):
    # Helper for running a Git command. Returns the rstrip()ed stdout output.
    # Called like git("diff"). Exits with SystemError (raised by sys.exit()) on
    # errors. 'cwd' is the working directory to use (default: current
    # directory).

    git_cmd = ("git",) + args
    try:
        git_process = subprocess.Popen(
            git_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwd)
    except OSError as e:
        err(f"failed to run '{cmd2str(git_cmd)}': {e}")

    stdout, stderr = git_process.communicate()
    stdout = stdout.decode("utf-8")
    stderr = stderr.decode("utf-8")
    if git_process.returncode or stderr:
        err(f"""\
'{cmd2str(git_cmd)}' exited with status {git_process.returncode} and/or wrote
to stderr.

==stdout==
{stdout}
==stderr==
{stderr}""")

    return stdout.rstrip()


def get_shas(refspec):
    """
    Returns the list of Git SHAs for 'refspec'.

    :param refspec:
    :return:
    """
    return git('rev-list',
               '--max-count={}'.format(-1 if "." in refspec else 1),
               refspec).split()


class MyCase(TestCase):
    """
    Custom junitparser.TestCase for our tests that adds some extra <testcase>
    XML attributes. These will be preserved when tests are saved and loaded.
    """
    classname = Attr()
    # Remembers informational messages. These can appear on successful tests
    # too, where TestCase.result isn't set.
    info_msg = Attr()


class ComplianceTest:
    """
    Base class for tests. Inheriting classes should have a run() method and set
    these class variables:

    name:
      Test name

    doc:
      Link to documentation related to what's being tested

    path_hint:
      The path the test runs itself in. This is just informative and used in
      the message that gets printed when running the test.

      The magic string "<git-top>" refers to the top-level repository
      directory. This avoids running 'git' to find the top-level directory
      before main() runs (class variable assignments run when the 'class ...'
      statement runs). That avoids swallowing errors, because main() reports
      them to GitHub.
    """
    def __init__(self):
        self.case = MyCase(self.name)
        self.case.classname = "Guidelines"

    def error(self, msg):
        """
        Signals a problem with running the test, with message 'msg'.

        Raises an exception internally, so you do not need to put a 'return'
        after error().

        Any failures generated prior to the error() are included automatically
        in the message. Usually, any failures would indicate problems with the
        test code.
        """
        if self.case.result:
            msg += "\n\nFailures before error: " + self.case.result._elem.text

        self.case.result = Error(msg, "error")

        raise EndTest

    def skip(self, msg):
        """
        Signals that the test should be skipped, with message 'msg'.

        Raises an exception internally, so you do not need to put a 'return'
        after skip().

        Any failures generated prior to the skip() are included automatically
        in the message. Usually, any failures would indicate problems with the
        test code.
        """
        if self.case.result:
            msg += "\n\nFailures before skip: " + self.case.result._elem.text

        self.case.result = Skipped(msg, "skipped")

        raise EndTest

    def add_failure(self, msg):
        """
        Signals that the test failed, with message 'msg'. Can be called many
        times within the same test to report multiple failures.
        """
        if not self.case.result:
            # First reported failure
            self.case.result = Failure(self.name + " issues", "failure")
            self.case.result._elem.text = msg.rstrip()
        else:
            # If there are multiple Failures, concatenate their messages
            self.case.result._elem.text += "\n\n" + msg.rstrip()

    def add_info(self, msg):
        """
        Adds an informational message without failing the test. The message is
        shown on GitHub, and is shown regardless of whether the test passes or
        fails. If the test fails, then both the informational message and the
        failure message are shown.

        Can be called many times within the same test to add multiple messages.
        """
        def escape(s):
            # Hack to preserve e.g. newlines and tabs in the attribute when
            # tests are saved to .xml and reloaded. junitparser doesn't seem to
            # handle it correctly, though it does escape stuff like quotes.
            # unicode-escape replaces newlines with \n (two characters), etc.
            return s.encode("unicode-escape").decode("utf-8")

        if not self.case.info_msg:
            self.case.info_msg = escape(msg)
        else:
            self.case.info_msg += r"\n\n" + escape(msg)


class EndTest(Exception):
    """
    Raised by ComplianceTest.error()/skip() to end the test.

    Tests can raise EndTest themselves to immediately end the test, e.g. from
    within a nested function call.
    """


class Uncrustify(ComplianceTest):
    """
    Runs checkpatch and reports found issues
    """
    name = "uncrustify"
    doc = "See ... for more details."
    path_hint = "<git-top>"

    def run(self):
        uncrustifyConfig = os.path.join(GIT_TOP, 'tools/uncrustify', 
                                        'uncrustify.cfg')
        if not os.path.exists(uncrustifyConfig):
            self.skip(uncrustifyConfig + " not found")

        repo = Repo(GIT_TOP)
        for fname in repo.git.diff('--name-only', '--diff-filter=d', 
                                    COMMIT_RANGE, 'source').splitlines():
            if not fname.startswith('source/portable') and \
               fname.endswith(('.c', '.h')):
                try:
                    subprocess.check_output((uncrustify, '-c', uncrustifyConfig, 
                                             '--check', '-q', '-l', 'c', fname),
                                            stderr=subprocess.STDOUT,
                                            shell=True, cwd=GIT_TOP)

                except subprocess.CalledProcessError as ex:
                    output = ex.output.decode("utf-8")
                    if re.search("^FAIL:\s", output):
                        self.add_info(output)

def init_logs(cli_arg):
    # Initializes logging

    # TODO: there may be a shorter version thanks to:
    # logging.basicConfig(...)

    global logger

    level = os.environ.get('LOG_LEVEL', "WARN")

    console = logging.StreamHandler()
    console.setFormatter(logging.Formatter('%(levelname)-8s: %(message)s'))

    logger = logging.getLogger('')
    logger.addHandler(console)
    logger.setLevel(cli_arg if cli_arg else level)

    logging.info("Log init completed, level=%s",
                 logging.getLevelName(logger.getEffectiveLevel()))



def parse_args():
    parser = argparse.ArgumentParser(
        description="Check for coding style and documentation warnings.")
    parser.add_argument('-c', '--commits', default="HEAD~1..",
                        help='''Commit range in the form: a..[b], default is
                        HEAD~1..HEAD''')
    parser.add_argument('-r', '--repo', default=None,
                        help="GitHub repository as <owner>/<name>")
    parser.add_argument('-p', '--pull-request', default=0, type=int,
                        help="Pull request number")
    parser.add_argument('-S', '--sha', default=None, help="Commit SHA")
    parser.add_argument('-o', '--output', default="compliance.xml",
                        help='''Name of outfile in JUnit format,
                        default is ./compliance.xml''')

    parser.add_argument('-l', '--list', action="store_true",
                        help="List all checks and exit")

    parser.add_argument("-v", "--loglevel", help="python logging level")

    parser.add_argument('-m', '--module', action="append", default=[],
                        help="Checks to run. All checks by default.")

    parser.add_argument('-e', '--exclude-module', action="append", default=[],
                        help="Do not run the specified checks")

    parser.add_argument('-j', '--previous-run', default=None,
                        help='''Pre-load JUnit results in XML format
                        from a previous run and combine with new results.''')

    return parser.parse_args()

def _main(args):
    # The "real" main(), which is wrapped to catch exceptions and report them
    # to GitHub. Returns the number of test failures.

    # The absolute path of the top-level git directory. Initialize it here so
    # that issues running Git can be reported to GitHub.
    global GIT_TOP
    GIT_TOP = git("rev-parse", "--show-toplevel")

    # The commit range passed in --commit, e.g. "HEAD~3"
    global COMMIT_RANGE
    COMMIT_RANGE = args.commits

    init_logs(args.loglevel)

    if args.list:
        for testcase in ComplianceTest.__subclasses__():
            print(testcase.name)
        return 0

    # Load saved test results from an earlier run, if requested
    if args.previous_run:
        if not os.path.exists(args.previous_run):
            # This probably means that an earlier pass had an internal error
            # (the script is currently run multiple times by the ci-pipelines
            # repo). Since that earlier pass might've posted an error to
            # GitHub, avoid generating a GitHub comment here, by avoiding
            # sys.exit() (which gets caught in main()).
            print("error: '{}' not found".format(args.previous_run),
                  file=sys.stderr)
            return 1

        logging.info("Loading previous results from " + args.previous_run)
        for loaded_suite in JUnitXml.fromfile(args.previous_run):
            suite = loaded_suite
            break
    else:
        suite = TestSuite("Compliance")

    for testcase in ComplianceTest.__subclasses__():
        # "Modules" and "testcases" are the same thing. Better flags would have
        # been --tests and --exclude-tests or the like, but it's awkward to
        # change now.

        if args.module and testcase.name not in args.module:
            continue

        if testcase.name in args.exclude_module:
            print("Skipping " + testcase.name)
            continue

        test = testcase()
        try:
            print(f"Running {test.name} tests in "
                  f"{GIT_TOP if test.path_hint == '<git-top>' else test.path_hint} ...")
            test.run()
        except EndTest:
            pass

        suite.add_testcase(test.case)

#   xml = JUnitXml()
#   xml.add_testsuite(suite)
#   xml.update_statistics()
#   xml.write(args.output, pretty=True)

#   failed_cases = []
#   name2doc = {testcase.name: testcase.doc
#                           for testcase in ComplianceTest.__subclasses__()}

#   for case in suite:
#       if case.result:
#           if case.result.type == 'skipped':
#               logging.warning("Skipped %s, %s", case.name, case.result.message)
#           else:
#               failed_cases.append(case)
#       else:
#           # Some checks like codeowners can produce no .result
#           logging.info("No JUnit result for %s", case.name)

#   n_fails = len(failed_cases)

#   if n_fails:
#       print("{} checks failed".format(n_fails))
#       for case in failed_cases:
#           # not clear why junitxml doesn't clearly expose the most
#           # important part of its underlying etree.Element
#           errmsg = case.result._elem.text
#           logging.error("Test %s failed: %s", case.name,
#                         errmsg.strip() if errmsg else case.result.message)

#           with open(f"{case.name}.txt", "w") as f:
#               docs = name2doc.get(case.name)
#               f.write(f"{docs}\n\n")
#               f.write(errmsg.strip() if errmsg else case.result.message)

    print("\nComplete results in " + args.output)
#   return n_fails
    return 0


def main():
    args = parse_args()

    try:
        n_fails = _main(args)
    except BaseException:
        # Catch BaseException instead of Exception to include stuff like
        # SystemExit (raised by sys.exit())
        print(format(__file__, traceback.format_exc()))

        raise

    sys.exit(n_fails)


def cmd2str(cmd):
    # Formats the command-line arguments in the iterable 'cmd' into a string,
    # for error messages and the like

    return " ".join(shlex.quote(word) for word in cmd)


def err(msg):
    cmd = sys.argv[0]  # Empty if missing
    if cmd:
        cmd += ": "
    sys.exit(cmd + "error: " + msg)


if __name__ == "__main__":
    main()
