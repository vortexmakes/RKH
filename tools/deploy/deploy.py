#!/usr/bin/python3

import sys
import argparse
import os
import shutil
import tarfile
import git
import re
from datetime import date
import fileinput
  
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

def printTitle(title):
    print("\n{}".format(title))
    print("{}".format('-' * len(title)))

def runRegressionTests():
    return

def updateVersion(repoPath, relVersion):
    versionFilePath = os.path.join(repoPath, 'source/fwk/inc/rkhfwk_version.h')
    relVersionNum = relVersion.replace('.', '')
    today = date.today().strftime("%m/%d/%Y")

    with fileinput.FileInput(versionFilePath, inplace = True) as verFile:
        for line in verFile:
            matchVersion = re.search(r"^#define\sRKH_VERSION_CODE\s+0x(?P<code>[0-9]{4})", line)
            matchDate = re.search(r"^\s\*\s+\\releasedate\s+(?P<date>[0-9]{1,2}/[0-9]{1,2}/[0-9]{2,4})", line)
            if matchVersion:
                if matchVersion.group('code') != relVersionNum:
                    print(line.replace(matchVersion.group('code'), 
                                       relVersionNum), end = '')
            elif matchDate:
                if matchDate.group('date') != today:
                    print(line.replace(matchDate.group('date'), today), end = '')
            else:
                print(line, end = '')

#   verFile = open(versionFilePath, 'r+')
#   for line in verFile:
#       matchVersion = re.search(r"^#define\sRKH_VERSION_CODE\s+0x(?P<code>[0-9]{4})", line)
#       matchDate = re.search(r"^\s\*\s+\\releasedate\s+(?P<date>[0-9]{1,2}/[0-9]{1,2}/[0-9]{2,4})", line)
#       if matchVersion:
#           if matchVersion.group('code') != relVersionNum:
#               print(line.replace(matchVersion.group('code'), 
#                                  relVersionNum), end = '')
#       elif matchDate:
#           print('date')
#           if matchDate.group('date') != today:
#               print(line.replace(matchDate.group('date'), today), end = '')
#   verFile.close()

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
            repo = git.Repo.clone_from(repoUrl, repoPath)
            print("Done")
        else:
            repo = git.Repo(repoPath)
            print('Repository {0:s} found in {1:s}'.format(repoName, repoPath))
        head = repo.active_branch
        if head.name != 'master':
            print("[WARNING] Must be realeased only from master branch")

        updateVersion(repoPath, version)
#       genDoc(repoPath)
#       build()
#       runRegressionTests()
#       publish()
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
