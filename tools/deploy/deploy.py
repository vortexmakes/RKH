#!/usr/bin/python3

import sys
import argparse
import os
import shutil
import tarfile
import git
  
GitHostURL = 'https://github.com/'

parser = argparse.ArgumentParser(
            add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description="Creates and publishes RKH's artifacts in order to "
                        "be released")

parser.add_argument('version', action="store", 
                    help='desired version. For example, 1.2.3 or 1.2.3-beta.1')
parser.add_argument('repository', action="store", 
                    help='specifies the repository info <owner>/<name>. '
                         'For example, itdelsat/CIM-ARM')
parser.add_argument('working', action="store", 
                    help='specifies the working directory')
parser.add_argument('changelog', action="store", 
                    help='text file describing the contents of the release')
parser.add_argument('token', action="store", metavar='token', 
                    help='personal access token')
parser.add_argument('-b', action="store", metavar='branch', default='master', 
                    help='specifies the commitish value that determines where '
                         'the Git tag is created from. Default: master')
parser.add_argument('-d', action="store_true", default=False,
                    help='creates a draft (unpublished) release')
parser.add_argument('-p', action="store_true", default=False,
                    help='identifies the release as a prerelease')


def deploy(version, repository, workingDir, changelog, token, 
           branch = "master", draft = False, prerelease = False):
    workingDir = os.path.expanduser(workingDir)
    repoName = repository.split('/')[-1]
    repoPath = os.path.join(workingDir, repoName)

    if os.path.isdir(workingDir):
        if not os.path.isdir(repoPath):
            os.mkdir(repoPath)
        if not os.path.isdir(os.path.join(repoPath, '.git')):
            repo = git.Repo.clone_from(GitHostURL + repository + '.git',
                                repoPath)
    else:
        print("ERROR: {0:s} does not exist".format(workingDir))
    return False

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        deploy(args.version, args.repository, args.working, args.changelog, 
               args.token, args.b, args.d, args.p)
    except IOError as msg:
        parser.error(str(msg))
