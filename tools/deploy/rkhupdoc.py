#!/usr/bin/python3

import sys
import argparse
import os
import re
from ftplib import FTP, error_perm

RKH_DOC_SEARH_DIR = 'search'
ROOT_DIR = '/'

parser = argparse.ArgumentParser(add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description="Updates RKH's docs using a ftp client")

parser.add_argument('server', action="store", 
                    help='FTP server')
parser.add_argument('user', action="store", 
                    help='FTP server user')
parser.add_argument('passwd', action="store", 
                    help='FTP server password')
parser.add_argument('dest', action="store", 
                    help='destination directory')
parser.add_argument('doc', action="store", 
                    help='doc directory to be uploaded')

class FtpAddOns():
    PATH_CACHE = []

    def __init__(self, ftp):
        self.ftp = ftp

    def pathExists(self, path):
        '''path exists check function for ftp handler'''
        exists = None
        if path not in self.PATH_CACHE:
            try:
                self.ftp.cwd(path)
                exists = True
                self.PATH_CACHE.append(path)
            except error_perm as reason:
                exists = False
        else:
            exists = True
        return exists


    def mkdirs(self, path, sep='/'):
        '''mkdirs function for ftp handler'''
        splitPath = path.split(sep)

        newDir = ''
        for serverDir in splitPath:
            if serverDir:
                newDir += sep + serverDir
                if not self.pathExists(newDir):
                    try:
                        print("Attempting to create directory %s ..." % newDir)
                        self.ftp.mkd(newDir)
                        print("Done!")
                    except error_perm as reason:
                        print('ERROR: ftp {}'.format(reason))

def _removeprefix(self: str, prefix: str, /) -> str:
    if self.startswith(prefix):
        return self[len(prefix):]
    else:
        return self[:]

def _findFiles(ftp, dirName):
    fileList = []
    foundFiles = []
    ftp.dir(fileList.append)
    for f in fileList[2:]:  # Ignore '.' and '..' directories
#   for f in fileList:
        split = f.split()
        attribute = split[0]
        name = split[-1]
        if attribute.startswith('-'):
            foundFiles.append(name)
    print('Found {0:d} files in \'{1:s}\''.format(len(foundFiles), dirName))
    return foundFiles

def _deleteFiles(ftp, dirName):
    files = []
    files = _findFiles(ftp, dirName)
    for f in files:
        ftp.delete(f)
    print('Deleted {0:d} files in \'{1:s}\''.format(len(files), dirName))

def _deleteDir(ftp, dirName, ftpPathTools):
    curDir = ftp.pwd()
    if ftpPathTools.pathExists(dirName):
        _deleteFiles(ftp, dirName)
        ftp.cwd(curDir)
        ftp.rmd(dirName)
        print('Deleted {0:s} directory'.format(dirName))
    else:
        print('{0:s} does not exist in server'.format(dirName))

def _getLocalFiles(localDir, walk = False):
    result = []
    
    baseDir = os.path.abspath(localDir)
    for currentDir, dirs, files in os.walk(baseDir):
        subDir = currentDir.replace(baseDir, '')

        if not walk and subDir:
            break

        for thisFile in files:
            filePath = os.path.join(currentDir, thisFile)
            fileMonitor = {'path': filePath, 'mtime': os.path.getmtime(filePath)}
            result.append(fileMonitor)
    return result

def _upload(ftp, local, remote, ftpPathTools):
    '''Private function. Upload all files in local directory to remote directory'''
    localFiles = []

    localDir = os.path.abspath(local)
    remoteDir = os.path.normpath(remote)
    localFiles = _getLocalFiles(localDir, True)

    if localFiles:
        for fileInfo in localFiles:
            filePath = fileInfo['path']
            path, fileName = os.path.split(filePath)
            remoteSubPath = path.replace(localDir, '')
            remoteSubPath = _removeprefix(remoteSubPath, '/')
            remotePath = path.replace(localDir, remoteDir)
            remotePath = remotePath.replace('\\', '/') # Convert to unix style

            if not ftpPathTools.pathExists(remotePath):
                ftpPathTools.mkdirs(remotePath)

            ftp.cwd(ROOT_DIR)
            ftp.cwd(remotePath)
            if os.path.exists(filePath):
                f = open(filePath, 'rb')
                fileName = os.path.split(f.name)[-1]
                displayFileName = os.path.join(remoteSubPath, fileName)
                displayFileName = displayFileName.replace('\\', '/')

                print("Sending %s ..." % displayFileName)
                sendCmd = 'STOR %s' % fileName
                ftp.storbinary(sendCmd, f)
                f.close()
                print("Done")
    else:
        print("ERROR: No files found in %s" % localDir)

def uploadDoc(server, user, password, remote, local):
    '''Upload all files on local directory to remote directory'''
    try:
        local = os.path.expanduser(local)
        if os.path.isdir(local):
            ftp = FTP(host=server, user=user, passwd=password)
            ftpPathTools = FtpAddOns(ftp)
            if ftpPathTools.pathExists(remote):
                _deleteFiles(ftp, remote)
                _deleteDir(ftp, RKH_DOC_SEARH_DIR, ftpPathTools)
                _upload(ftp, local, remote, ftpPathTools)
            else:
                print('ERROR: {0:s} does not exist in server'.format(remote))
            ftp.quit()
        else:
            print('ERROR: {} does not exist'.format(local))
    except error_perm as reason:
        print('ERROR: ftp {}'.format(reason))

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        uploadDoc(args.server, args.user, args.passwd, args.dest, args.doc)
    
    except IOError as msg:
        parser.error(str(msg))
    except error_perm as reason:
        print('ERROR: ftp {}'.format(reason))
