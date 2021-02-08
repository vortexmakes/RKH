#!/usr/bin/python3

import sys
import argparse
import os
import shutil
import tarfile
import git
from git import RemoteProgress
import re
from datetime import date
import fileinput
  
GitHostURL = 'https://github.com/'

class MyProgressPrinter(RemoteProgress):
    def update(self, op_code, cur_count, max_count=None, message=''):
        print(op_code, cur_count, max_count, 
              cur_count / (max_count or 100.0), message or "NO MESSAGE")

parser = argparse.ArgumentParser(
            add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description="Creates and publishes RKH's artifacts in order to "
                        "be released")

parser.add_argument('version', action="store", 
                    help='desired version. For example, 1.2.3 or 1.2.3-beta.1')
parser.add_argument('repository', action="store", 
                    help='specifies the repository info <owner>/<name>. '
                         'For example, vortexmakes/RKH')
parser.add_argument('working', action="store", 
                    help='specifies the working directory')
parser.add_argument('changelog', metavar='changelog-file', 
                    type=argparse.FileType('rt'), 
                    help='text file describing code changes')
parser.add_argument('token', action="store", metavar='token', 
                    help='personal access token')
parser.add_argument('-b', action="store", metavar='branch', default='master', 
                    help='specifies the commitish value that determines where '
                         'the Git tag is created from. Default: master')
parser.add_argument('-d', action="store_true", default=False,
                    help='creates a draft (unpublished) release')
parser.add_argument('-p', action="store_true", default=False,
                    help='identifies the release as a prerelease')

def printTitle(title):
    print("\n{}".format(title))
    print("{}".format('-' * len(title)))

def updateVersion(repoPath, relVersion):
    versionFilePath = os.path.join(repoPath, 'source/fwk/inc/rkhfwk_version.h')
    relVersionNum = relVersion.replace('.', '')
    today = date.today().strftime("%m/%d/%Y")
    isFoundVersionPattern = None
    isFoundDatePattern = None

    printTitle("Updating version")
    with fileinput.FileInput(versionFilePath, inplace = True) as verFile:
        for line in verFile:
            matchVersion = re.search(r"^#define\sRKH_VERSION_CODE\s+0x(?P<code>[0-9]{4})", line)
            matchDate = re.search(r"^\s\*\s+\\releasedate\s+(?P<date>[0-9]{1,2}/[0-9]{1,2}/[0-9]{2,4})", line)
            if matchVersion:
                if matchVersion.group('code') != relVersionNum:
                    print(line.replace(matchVersion.group('code'), 
                                       relVersionNum), end = '')
                    isFoundVersionPattern = True
            elif matchDate:
                if matchDate.group('date') != today:
                    print(line.replace(matchDate.group('date'), today), end = '')
                    isFoundDatePattern = True
            else:
                print(line, end = '')

    if isFoundDatePattern and isFoundVersionPattern:
        print("Updated version: {}".format(relVersion))
        print("Updated version date: {}".format(today))
    else:
        print("[ERROR] Unknown version file format")

def updateChangeLog():
    return

def updateBranches(repo):
    print("Updating default branch from develop")

def genDoc(repoPath):
    printTitle("Generating doc (html) using doxygen")
    curDir = os.getcwd()
    os.chdir(os.path.join(repoPath, "doc"))
    os.system('doxygen Doxyfile')
    os.chdir(curDir)
    print("Done")

def deploy(version, repository, workingDir, changelog, token, 
           branch = "master", draft = False, prerelease = False):
    workingDir = os.path.expanduser(workingDir)
    repoName = repository.split('/')[-1]
    repoPath = os.path.join(workingDir, repoName)

    printTitle("Verifying directories, files and version")
    if not re.match(r'[0-9].[0-9].[0-9]{2}', version):
        print("[ERROR] Invalid version code: {}".format(version))
        return
        
    if os.path.isdir(workingDir):
        if not os.path.isdir(repoPath):
            os.mkdir(repoPath)
        if not os.path.isdir(os.path.join(repoPath, '.git')):
            repoUrl = GitHostURL + repository + '.git'
            print("Cloning repository from {}...".format(repoUrl))
            repo = git.Repo.clone_from(repoUrl, repoPath, 
                                       progress=MyProgressPrinter())
            # Setup a local tracking branch of a remote branch
            ## create local branch "master" from remote "master"
            origin = repo.remotes['origin']
            repo.create_head('develop', origin.refs.develop)
            ## set local "develop" to track remote "develop"
            repo.heads.develop.set_tracking_branch(origin.refs.develop)
            ## checkout local "develop" to working tree
            repo.heads.develop.checkout()
            print("Done")
        else:
            repo = git.Repo(repoPath)
            print('Repository {0:s} found in {1:s}'.format(repoName, repoPath))
            if repo.is_dirty():
                print("[ERROR] Repository is dirty:")
                print("{}".format(repo.git.diff('--name-only')))
                return
            if repo.active_branch.name != 'develop':
                print("[ERROR] It process must only be performed on " +
                      "develop branch")
                return
            origin = repo.remotes['origin']
            origin.pull(progress=MyProgressPrinter())

        updateVersion(repoPath, version)
#       updateChangeLog()
#       genDoc(repoPath)
#       publishDoc()
#       updateBranches(repo)
#       updateDftBranch()
#       createPackage()
#       release()
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
