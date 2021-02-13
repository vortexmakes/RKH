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
import json
import subprocess
from rkhupdoc import uploadDoc
import time
  
GitHostURL = 'https://github.com/'
CHANGELOG_PATH = 'tools/deploy/changelog.json'
DOC_CHANGELOG_PATH = 'doc/chglog.txt'

class DeployError(Exception):
    pass

class Release:
    header = ""
    tail = ""
    version = ""
    date = ""
    new = []
    bugfix = []
    apichg = []
    deprecated = []
    port = []
    note = []

    def __init__(self, relDic):
        self.version = relDic['version']
        self.date = relDic['date']
        self.new = relDic['new']
        self.bugfix = relDic['bugfix']
        self.apichg = relDic['apichg']
        self.deprecated = relDic['deprecated']
        self.port = relDic['port']
        self.note = relDic['note']

    def message(self, kindOf, messages):
        section = ""
        if len(messages) != 0:
            section = "{}\n".format(self.MsgType[kindOf])
            for line in messages:
                section += "- " + line + '\n'
            section += '\n'
        return section

    def news(self):
        return self.message('new', self.new)

    def bugfixes(self):
        return self.message('bugfix', self.bugfix)

    def apichanges(self):
        return self.message('apichg', self.apichg)

    def deprecatedFeatures(self):
        return self.message('deprecated', self.deprecated)

    def notes(self):
        return self.message('note', self.note)

class RelMsg(Release):
    HeaderText = ""
    TailText = ""
    MsgType = {"new": '**New features**',
               "bugfix": '**Bug fixes**', 
               "apichg": '**API changes**',
               "deprecated": '**Deprecated features**',
               "note": '**Notes**'}

    def __init__(self, relDic):
        super().__init__(relDic)
        self.header = self.HeaderText
        self.tail = self.TailText

class RelLog(Release):
    HeaderText = "/**\n\page changelog Release Notes\n\n\\tableofcontents\n\n"
    TailText = "\n*/"
    MsgType = {"new": '\\new',
               "bugfix": '\\bugfix', 
               "apichg": '\\apichg',
               "deprecated": '\\deprecated',
               "note": '\\warning'}

    def __init__(self, relDic):
        super().__init__(relDic)
        self.header = self.HeaderText
        self.tail = self.TailText

    def section(self):
        verCode = self.version.split('.')
        line = "\section rkhVer_"
        line += "{0:s}_{1:s}_{2:s} ".format(verCode[0], verCode[1], verCode[2])
        line += "Version {}\n".format(self.version)
        return line

    def relDate(self):
        line = "\\releasedate {}\n\n".format(self.date)
        return line

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

def printTaskTitle(title):
    print("{}...".format(title))

def printTaskDone():
    print("{}".format('Done'))

def updateVersion(repoPath, relVersion):
    versionFilePath = os.path.join(repoPath, 'source/fwk/inc/rkhfwk_version.h')
    relVersionNum = relVersion.replace('.', '')
    today = date.today().strftime("%m/%d/%Y")
    isFoundVersionPattern = None
    isFoundDatePattern = None

    printTaskTitle("Updating version")
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
        raise DeployError("\nAbort: unknown version file format")

def genChangeLog(repo, inFilePath, outFilePath):
    printTaskTitle("Generating change log file")
    if os.path.exists(inFilePath):
        jsonFile = open(inFilePath, 'r')
        releases = json.load(jsonFile)
        jsonFile.close()

        with open(outFilePath, "w+") as relfile:
            latest = RelMsg(releases[0])
            relfile.write(latest.header)    # Add the header file

            for release in releases:
                rel = RelLog(release)
                text = rel.section() 
                relfile.write(text)
                text = rel.relDate()
                relfile.write(text)
                text = rel.news()
                relfile.write(text)
                text = rel.bugfixes()
                relfile.write(text)
                text = rel.apichanges()
                relfile.write(text)
                text = rel.deprecatedFeatures()
                relfile.write(text)
                text = rel.notes()
                relfile.write(text)

            relfile.write(latest.tail)      # Add the tail file
            printTaskDone()
    else:
        raise DeployError("\nAbort: Release file {} does not exist".format(inFilePath))
    return

def genRelMsg(repo, inFilePath):
    printTaskTitle("Generating release message")
    if os.path.exists(inFilePath):
        jsonFile = open(inFilePath, 'r')
        releases = json.load(jsonFile)
        jsonFile.close()

        release = RelMsg(releases[0])
        text = release.header     # Add the message header

        text += release.news()
        text += release.bugfixes()
        text += release.apichanges()
        text += release.deprecatedFeatures()
        text += release.notes()

        text += release.tail       # Add the message tail
        printTaskDone()
        return text
    else:
        raise DeployError("\nAbort: Release file {} does not exist".format(inFilePath))
    return

def updateBranches(repo):
    printTaskTitle("Updating branch develop")
    if repo.active_branch.name == 'develop':
        mfiles = repo.git.diff('--name-only').split('\n')
        files = ['doc/chglog.txt', 'source/fwk/inc/rkhfwk_version.h']
        if files == mfiles:
            repo.index.add(mfiles)
            repo.index.commit("Updated version and log of code changes")
            print('Committed {} files'.format(mfiles))
            printTaskDone()
        else:
            raise DeployError("\nAbort: Cannot update develop branch")
    else:
        raise DeployError("\nAbort: Cannot update develop branch")

    printTaskTitle("Integrating develop onto master")
    repo.git.checkout('master')
    proc = subprocess.run('git merge develop', shell=True,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT, 
                          cwd=repo.working_dir)
    if proc.returncode != 0:
        raise DeployError("\nAbort: Cannot integrate develop onto master")
    printTaskDone()

    printTaskTitle("Updating remote branch develop")
    printTaskDone()
    printTaskTitle("Updating remote branch master")
    printTaskDone()

def genDoc(repoPath):
    printTaskTitle("Generating doc (html) using doxygen")
    docPath = os.path.join(repoPath, 'doc')
    proc = subprocess.run("doxygen Doxyfile", shell=True, 
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT, 
                          cwd=docPath)
    if proc.returncode != 0:
        raise DeployError("\nAbort: Doxygen fails:\n{}".format(proc.stdout))
    else:
        printTaskDone()

def publishDoc(server, user, passwd, dest, doc):
    uploadDoc(server, user, passwd, dest, doc)

def deploy(version, repository, workingDir, token, 
           branch = "master", draft = False, prerelease = False):
    workingDir = os.path.expanduser(workingDir)
    repoName = repository.split('/')[-1]
    repoPath = os.path.join(workingDir, repoName)

    printTaskTitle("Verifying directories, files and code version")
    if not re.match(r'[0-9].[0-9].[0-9]{2}', version):
        raise DeployError("\nAbort: Invalid version code: {}".format(version))
        
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
            printTaskDone()
        else:
            repo = git.Repo(repoPath)
            print('Repository {0:s} found in {1:s}'.format(repoName, repoPath))
            if repo.is_dirty():
                raise DeployError("\nAbort: Repository is dirty")
            if repo.active_branch.name != 'develop':
                raise DeployError("\nAbort: It process must only be performed on " +
                                  "develop branch")
            origin = repo.remotes['origin']
            origin.pull(progress=MyProgressPrinter())
            printTaskDone()

        updateVersion(repoPath, version)
        genChangeLog(repo, os.path.join(repo.working_dir, CHANGELOG_PATH),
                     os.path.join(repo.working_dir, DOC_CHANGELOG_PATH))
        relMsg = genRelMsg(repo, os.path.join(repo.working_dir, CHANGELOG_PATH))
#       genDoc(repoPath)
#       publishDoc('ftp.vortexmakes.com',
#                  'webmaster.vortexmakes.com',
#                  'V0rt3xM4k35!',
#                  'htdocs/rkh/lolo',
#                  '~/lolo/')
        updateBranches(repo)
#       createPackage()
#       release(relMsg)
    else:
        raise DeployError("\nAbort: {0:s} does not exist".format(workingDir))
    return False

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        deploy(args.version, args.repository, args.working, 
               args.token, args.b, args.d, args.p)
    except IOError as msg:
        parser.error(str(msg))
    except DeployError as e:
        print(e)
