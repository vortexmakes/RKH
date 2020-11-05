#!/usr/bin/python3

import sys
import argparse
from github import Github, GithubException, GitRelease
import os
import shutil
import tarfile

parser = argparse.ArgumentParser(
            add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description='Creates and publishes a release in a GitHub '
                        'repository')

parser.add_argument('version', action="store", 
                    help='desired version. For example, 1.2.3 or 1.2.3-beta.1')
parser.add_argument('repository', action="store", 
                    help='specifies the repository info <owner>/<name>. '
                         'For example, itdelsat/CIM-ARM')
parser.add_argument('package', action="store", 
                    help='specifies the directory or tar.gz package in order '
                         'to publish it')
parser.add_argument('-b', action="store", metavar='branch', default='master', 
                    help='specifies the commitish value that determines where '
                         'the Git tag is created from. Default: master')
parser.add_argument('changelog', action="store", 
                    help='text file describing the contents of the release')
parser.add_argument('-d', action="store_true", default=False,
                    help='creates a draft (unpublished) release')
parser.add_argument('-p', action="store_true", default=False,
                    help='identifies the release as a prerelease')
parser.add_argument('token', action="store", metavar='token', 
                    help='personal access token')

def upload_file(repository, package, release):
    '''
    Upload a file to latest release
    '''
    try:
        print("Uploading file " + 
              "{0:s} to {1:s} repository...".format(package, repository.name))
        release.upload_asset(package, '', 'application/gzip', package)
    except GithubException as ex:
        print("ERROR: cannot upload file + "
              "{0:s} to {1:s} release. Error code ({2:d})".format(package, 
                                                   release.tag_name, ex.status))
        raise
    print("Upload file {0:s} to {1:s} release".format(package, 
                                                      release.tag_name))

def create_release(repository, version, changelog, draft, prerelease):
    try:
        print("Creating release " +
              "{0:s} of {1:s} repository...".format(version, repository.name))
        name = 'v' + version
        changelogPath = os.path.normpath(os.path.expanduser(changelog))
        changelogFile = open(changelogPath, 'r')
        msg = changelogFile.read()
        changelogFile.close()
        release = repository.create_git_release(name, name, msg, draft, prerelease, 
                                                "master")
        print("Release {0:s} published in {1:s} repository".format(name, 
                                                                   repository.name))
    except GithubException as ex:
        print("ERROR: cannot create release " +
              "{0:s}. Error code ({1:d})".format(version, ex.status))
        raise
    return release

def isNotLocal(dir):
    if dir != "" and dir != '.' and dir != os.getcwd():
        return True
    else:
        return False

def releasePkg(version, repository, package, changelog, token, 
               branch = "master", draft = False, prerelease = False):
    try:
        result = True
        g = Github(token)
        repo = g.get_repo(repository)
        release = create_release(repo, version, changelog, draft, prerelease)
        dirExp = os.path.normpath(os.path.expanduser(package))
        if os.path.exists(dirExp):
            curDir = os.getcwd()
            dirPath = os.path.dirname(dirExp)
            dirName = os.path.basename(dirExp)
            if os.path.isdir(dirExp):
                if isNotLocal(dirPath):
                    if os.path.exists(dirName) == True: # Setup
                        print("Delete old '{0:s}' in '{1:s}'".format(dirName, 
                                                                     curDir))
                        shutil.rmtree(dirName)
                    print("Copy '{0:s}' to '{1:s}'".format(dirName, curDir))
                    shutil.copytree(dirExp, os.path.join(curDir, dirName))
                print("Compressing '{}'...".format(dirName))
                file = shutil.make_archive(os.path.join(curDir, dirName), 
                                           'gztar', 
                                           os.path.join(curDir, dirName))
                upload_file(repo, os.path.basename(file), release)
                if isNotLocal(dirPath): # Cleanup
                    print("Delete '{0:s}' in '{1:s}'".format(dirName, curDir))
                    shutil.rmtree(dirName)
                    print("Delete '{0:s}' in '{1:s}'".format(file, curDir))
                    os.remove(file)
            else:
                if tarfile.is_tarfile(dirExp):
                    if isNotLocal(dirPath):
                        shutil.copy2(dirExp, curDir)
                        upload_file(repo, os.path.basename(dirExp), release)
                        print("Delete '{0:s}' in '{1:s}'".format(dirName, 
                                                                 curDir))
                        os.remove(dirName)
                else:
                    print('ERROR: {} is not a valid tar file'.format(package))
                    result = False
        else:
            print('ERROR: {} is not found'.format(package))
            result = False
        return result

    except GithubException as msg:
        print("ERROR: message from Github: {}".format(msg.data))

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        releasePkg(args.version, args.repository, args.package, args.changelog, 
                   args.token, args.b, args.d, args.p)
    except IOError as msg:
        parser.error(str(msg))
    except GithubException as msg:
        print("ERROR: message from Github: {}".format(msg.data))
