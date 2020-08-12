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
import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable

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

    def addText(self, value):
        self.textSize += int(value, 0)

    def addData(self, value):
        self.dataSize += int(value, 0)

    def addRoData(self, value):
        self.rodataSize += int(value, 0)

    def add(self, section, value):
        switcher = {
        'bss': self.addBss,
        'text': self.addText,
        'data': self.addData,
        'rodata': self.addRoData
        }
        func = switcher.get(section)
        func(value)
        

parser = argparse.ArgumentParser(
            add_help=True,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description = "Calculates the code size of RKH's source files from "
                          "a standard ARM .map file")

parser.add_argument('mapFile', metavar='map-file', 
                    type=argparse.FileType('rt'), 
                    help='Map file')

parser.add_argument('-p','--path', default='../../source/',
                    help='Path to source files',
                    dest='pathToSource')

def createFilesDic(dic, module):
    fileList = []
    path = args.pathToSource + module + '/src' 
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

        print('--------- Parsing objects ---------')
        args.mapFile.seek(0, 0)
        reMatch = False
        temp = ''
        for line in args.mapFile:
            if reMatch :
                # See further down
                line = temp + line # If we had a multiline .bss, concatenate and reuse common regex
                reMatch = False

            match = re.search(r"\.bss[\S+|\s+]+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+/src/(?P<module>\S+).o)", line)
            match = re.search(r"\.(?P<section>(bss|text|data|rodata){1})[\S+|\s+]+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+/src/(?P<module>\S+).o)", line)

            if match:
                #print(match.group('section','size', 'module'))
                #print(match.group('size', 2, 'module'))
                fileName = match.group('module')
                for module in modules.values():
                    if fileName in module:
                        module[fileName].add(match.group('section'),match.group('size'))
                        break
            else:
                if re.search(r"\.(bss|text|data|rodata){1}[\S+|\s+]+\n", line):
                    # We have a multiline .bss record
                    temp = line[:-1] #We store the starting line without \n
                    reMatch = True

        x = PrettyTable()
        x.field_names = ["Module", ".bss", ".text", ".data", ".rodata"]
        x.align["Module"] = "l"
        x.align[".bss"] = "r"
        x.align[".text"] = "r"
        x.align[".data"] = "r"
        x.align[".rodata"] = "r"
        for key in modules.keys():
            for fil in modules[key].values():
                x.add_row([fil.name, fil.bssSize, fil.textSize, fil.dataSize, fil.rodataSize])
                #print('Size of bss section for {0:s}: {1:d} (0x{1:x})'.format(fil.name, fil.bssSize))
        x.sortby = "Module"
        print(x)

#       print('--------- Find .data objects ---------')
#       args.mapFile.seek(0, 0)
#       for line in args.mapFile:
#           match = re.search(r"\.data\s+0x[\dabdcef]+\s+(0x[\dabcdef]+)\s(\S+[rkh|RKH]/source/\S+/src/\S+.o)", line)
#           if match:
#               print(match.group(1) + ' ' + match.group(2))

        args.mapFile.close()

        # Make a dataset:
        heightBss = list()
        heightText = list()
        heightData = list()
        heightRodata = list()
        bars = list()
        for key in modules.keys():
            for fil in modules[key].values():
                heightBss.append(fil.bssSize)
                heightText.append(fil.textSize)
                heightData.append(fil.dataSize)
                heightRodata.append(fil.rodataSize)
                bars.append(fil.name)

        y_pos = np.arange(len(bars))

        # Create bars
        bss = plt.bar(y_pos, heightBss)
        text = plt.bar(y_pos, heightText)
        data = plt.bar(y_pos, heightData)
        rodata = plt.bar(y_pos, heightRodata)

        plt.legend((bss[0], text[0], data[0], rodata[0]), ('.bss', '.text', '.data', 'rodata'))

        # Add title and axis names
        plt.title('Size of all sections')
        plt.ylabel('Bytes', fontweight='bold', color=(0.2, 0.4, 0.6, 0.6), fontsize='10')

        # Create names on the x-axis
        plt.xticks(y_pos, bars, rotation = 90)

        # Text on the top of each barplot
        #for i in range(len(bars)):
        #    plt.text(x = y_pos[i] - 0.5, y = height[i] + 0.3, s = height[i], size = 8)

        # Custom the subplot layout
        plt.subplots_adjust(bottom=0.3, top=0.95)

#       # Save plot as png
#       plt.savefig('foo.png', bbox_inches = 'tight')

#       # Show graphic
        plt.show()
    except IOError as msg:
        parser.error(str(msg))
