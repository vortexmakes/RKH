#!/usr/bin/python3
""" 
This program calculates the code size of RKH's source files from a standard 
ARM .map file
""" 

import sys
import argparse
import os
import shutil
import re

class FileObj:
    textSize = 0
    rodataSize = 0
    dataSize = 0
    bssSize = 0
    name = ''

    def __init__(self, name):
        self.name = name

    def addBss(self, value):
        self.bssSize += int(value, 0)

parser = argparse.ArgumentParser(
            add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description = "Calculates the code size of RKH's source files from "
                          "a standard ARM .map file")

parser.add_argument('mapFile', metavar='map-file', 
                    type=argparse.FileType('rt'), 
                    help='Map file')

def createFilesDic(dic, module):
    fileList = []
    path = '../../source/' + module + '/src' 
    l = os.listdir(path)
    for f in l:
        fileList.append(FileObj(os.path.splitext(f)[0]))
    for f in fileList:
        dic[f.name] = f

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])

        modules = {'fwk': {}, 'trc': {}, 'tmr': {}, 'sma': {}, 
                   'sm': {}, 'mempool': {}, 'queue': {}}

        for key in modules.keys():
            createFilesDic(modules[key], key)
            
#       print('--------- Find .txt objects ---------')
#       firstMatchText = False
#       for line in args.mapFile:
#           if firstMatchText == False:
#               if re.search(r"\s\.text\.\S+", line):
#                   firstMatchText = True
#           else:
#               firstMatchText = False
#               match = re.search(r"\s+0x[\dabcdef]+\s+(0x[\dabcdef]+)\s(\S+[rkh|RKH]/source/\S+/src/\S+.o)", line)
#               if match:
#                   print(match.group(1) + ' ' + match.group(2))

#       print('--------- Find .rodata objects ---------')
#       args.mapFile.seek(0, 0)
#       for line in args.mapFile:
#           match = re.search(r"\.rodata\s+0x[\dabdcef]+\s+(0x[\dabcdef]+)\s(\S+[rkh|RKH]/source/\S+/src/\S+.o)", line)
#           if match:
#               print(match.group(1) + ' ' + match.group(2))

        print('--------- Find .bss objects ---------')
        args.mapFile.seek(0, 0)
        for line in args.mapFile:
            match = re.search(r"\.bss\s+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+[rkh|RKH]/source/\S+/src/(?P<module>\S+).o)", line)
            if match:
                print(match.group('size', 2, 'module'))
                fileName = match.group('module')
                for module in modules.values():
                    if fileName in module:
                        module[fileName].addBss(match.group('size'))
                        break

        for key in modules.keys():
            for fil in modules[key].values():
                print('Size of bss section for {0:s}: {1:d} (0x{1:x})'.format(fil.name, fil.bssSize))

#       print('--------- Find .data objects ---------')
#       args.mapFile.seek(0, 0)
#       for line in args.mapFile:
#           match = re.search(r"\.data\s+0x[\dabdcef]+\s+(0x[\dabcdef]+)\s(\S+[rkh|RKH]/source/\S+/src/\S+.o)", line)
#           if match:
#               print(match.group(1) + ' ' + match.group(2))

        args.mapFile.close()
    except IOError as msg:
        parser.error(str(msg))
