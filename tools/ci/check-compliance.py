#!/usr/bin/env python3

import sys
import subprocess
import re
import os
import logging
import argparse
from junitparser import TestCase, TestSuite, JUnitXml, Skipped, Error, Failure, Attr
from pathlib import Path
from git import Repo
import traceback

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
    Runs uncrustify and reports found issues
    """
    name = "Uncrustify"
    doc = "See ... for more details."
    path_hint = "<git-top>"

    def run(self):
        config = os.path.join(GIT_TOP, 'tools/uncrustify', 'uncrustify.cfg')
        if not os.path.exists(config):
            self.skip(config + " not found")

        repo = Repo(GIT_TOP)
        for fname in repo.git.diff('--name-only', '--diff-filter=d', 
                                    COMMIT_RANGE, 'source').splitlines():
            if not fname.startswith('source/portable') and \
               fname.endswith(('.c', '.h')):
                try:
                    subprocess.check_output(['uncrustify', '-c', config, 
                                             '--check', '-q', '-l', 'c', fname],
                                            stderr=subprocess.STDOUT,
                                            cwd=GIT_TOP)

                except subprocess.CalledProcessError as ex:
                    output = ex.output.decode("utf-8")
                    if re.search("^FAIL:\s", output):
                        self.add_info(output)

class Identity(ComplianceTest):
    """
    ...
    """
    name = "Identity"
    doc = "See ... for more details."
    path_hint = "<git-top>"

    def run(self):
        repo = Repo(GIT_TOP)
        limit = -1 if '.' in COMMIT_RANGE else 1
        regex = '^[a-z0-9]+[\._]?[a-z0-9]+[@]\w+[.]\w{2,3}$' # Valid email address
        failure = None
        for commit in list(repo.iter_commits(COMMIT_RANGE, max_count=limit)):
            match = re.search(regex, commit.author.email)
            if not match:
                failure = "%s: author email (%s) must be a valid " \
                          "email address." % (commit.hexsha, commit.author.email)
            if len(commit.author.name.split(' ')) < 2:
                if failure:
                   failure += "\n"
                failure += "%s: author name (%s) does not follow " \
                           "the syntax: First Last <email>." \
                           % (commit.hexsha, commit.author.name)
        if failure:
            self.add_failure(failure)

def init_logs(loglevel):
    numericLevel = getattr(logging, loglevel.upper(), None)
    if not isinstance(numericLevel, int):
        raise ValueError('Invalid log level: %s' % loglevel)
    logging.basicConfig(format='%(levelname)-8s: %(message)s', level=numericLevel)
    logging.info("Log init completed, level=%s",
                 logging.getLevelName(logging.getLogger().getEffectiveLevel()))

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
    parser.add_argument("-v", "--loglevel", default='WARNING', 
                        help="python logging level")
    parser.add_argument('-t', '--test', action="append", default=[],
                        help='''Check to run. Use --list to see available
                        checks.''')
    parser.add_argument('-e', '--exclude-test', action="append", default=[],
                        help="Do not run the specified check")
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
    repo = Repo()
    GIT_TOP = repo.working_dir

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
        if args.test and testcase.name not in args.test:
            continue

        if testcase.name in args.exclude_test:
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

    xml = JUnitXml()
    xml.add_testsuite(suite)
    xml.update_statistics()
    xml.write(args.output, pretty=True)

    failed_cases = []
    name2doc = {testcase.name: testcase.doc
                            for testcase in ComplianceTest.__subclasses__()}

    for case in suite:
        if case.result:
            if case.result.type == 'skipped':
                logging.warning("Skipped %s, %s", case.name, case.result.message)
            else:
                failed_cases.append(case)
        else:
            # Some checks can produce no .result
            logging.info("No JUnit result for %s", case.name)

    n_fails = len(failed_cases)

    if n_fails:
        print("{} checks failed".format(n_fails))
        for case in failed_cases:
            # not clear why junitxml doesn't clearly expose the most
            # important part of its underlying etree.Element
            errmsg = case.result._elem.text
            logging.error("Test %s failed: %s", case.name,
                          errmsg.strip() if errmsg else case.result.message)

            with open(f"{case.name}.txt", "w") as f:
                docs = name2doc.get(case.name)
                f.write(f"{docs}\n\n")
                f.write(errmsg.strip() if errmsg else case.result.message)

    print("\nComplete results in " + args.output)
    return n_fails

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

if __name__ == "__main__":
    main()
