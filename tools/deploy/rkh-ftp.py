#!/usr/bin/python3

import sys
import argparse
import os
import re
from ftplib import FTP, error_perm

RKH_DOC_SEARH_DIR = 'search'

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

def findFiles(dirName):
    fileList = []
    foundFiles = []
    ftp.dir(fileList.append)
    for f in fileList[2:]:
        split = f.split()
        attribute = split[0]
        name = split[-1]
        if attribute.startswith('-'):
            foundFiles.append(name)
    print('Found {0:d} files in \'{1:s}\''.format(len(foundFiles), dirName))
    return foundFiles

def deleteFiles(dirName):
    files = []
    files = findFiles(dirName)
    for f in files:
        ftp.delete(f)
    print('Deleted {0:d} files in \'{1:s}\''.format(len(files), dirName))

def deleteDir(dirName):
    curDir = ftp.pwd()
    ftp.cwd(dirName)
    deleteFiles(dirName)
    ftp.cwd(curDir)
    ftp.rmd(dirName)
    print('Deleted {0:s} directory'.format(dirName))

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        if os.path.isdir(args.doc):
            ftp = FTP(host=args.server, user=args.user, passwd=args.passwd)
            directory = args.dest
            ftp.cwd(directory)
            deleteFiles(directory)
            deleteDir('toto')   # delete RKH_DOC_SEARH_DIR directory
            # Upload doc to 'htdocs/rkh'
            ftp.quit()
        else:
            print('ERROR: {} does not exist'.format(args.doc))
    
    except IOError as msg:
        parser.error(str(msg))
    except error_perm as reason:
        print('ERROR: ftp {}'.format(reason))
