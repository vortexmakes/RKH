#!/usr/bin/python3

import sys
import argparse
import os
import re
from ftplib import FTP

RKH_DOC_PATH = 'htdocs/rkh'
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

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])
        if os.path.isdir(args.doc):
            ftp = FTP(host=args.server, user=args.user, passwd=args.passwd)
            ftp.cwd(RKH_DOC_PATH)
            lst = []
            files = []
            dirs = []
            ftp.dir(lst.append)
            for f in lst[2:]:
                match = re.search(r'^(?P<type>[d-])\S+\s+\d+\s\S+\s+\S+\s+\d+\s\S+\s+\d+\s+\d+\s(?P<name>\S+)', f)
                if match.group('type') == '-':
                    files.append(match.group('name'))
                elif match.group('type') == 'd':
                    dirs.append(match.group('name'))
                else:
                    print('Unknonw file entry')
            print('Found {0:d} files in \'{1:s}\''.format(len(files), RKH_DOC_PATH))
            print('Found {0:d} directories in \'{1:s}\''.format(len(dirs), RKH_DOC_PATH))
                    
            # Delete 'htdocs/rkh' content
            # Upload doc to 'htdocs/rkh'
            ftp.quit()
        else:
            print('ERROR: {} does not exist'.format(args.doc))
    
    except IOError as msg:
        parser.error(str(msg))
