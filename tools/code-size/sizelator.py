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
import plotly.graph_objects as go
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

parser.add_argument('-g','--graph', default='none',
                    help='Plot library to use: matplot | plotly | none',
                    dest='plotType')

def createFilesDic(dic, module):
    fileList = []
    path = args.pathToSource + module + '/src' 
    l = os.listdir(path)
    for f in l:
        fileList.append(FileObj(os.path.splitext(f)[0]))
    for f in fileList:
        dic[f.name] = f

def addToModule(modules, fileName, section, size):
    for module in modules.values():
        if fileName in module:
            module[fileName].add(section, size)
            break

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
        checkFill = False
        temp = ''
        fastForwarding = True
        for line in args.mapFile:
            if fastForwarding:
                # Speedup 'til sections of interest
                match = re.search(r"^\.(bss|text|data|rodata){1}\s+0x\w+\s+0x\w+", line)
                if match:
                    fastForwarding = False
            else:
                if re.search(r"\.((debug_(info|abbrev|aranges|ranges|macro|line|str){1})|comment|stack)\s+0x\w+\s+0x\w+", line):
                    # Skip other info between sections
                    line=''
                    continue
                if reMatch :
                    # See further down
                    line = temp + line # If we had a multiline .bss, concatenate and reuse common regex
                    reMatch = False
                if checkFill:
                    # See further down
                    fillMatch = re.search(r"\*fill\*\s+0x\w+\s+(?P<size>0x[\dabcdef]+)\s(\w+)?\n", line)
                    if fillMatch:
                        addToModule(modules, match.group('module'), match.group('section'),fillMatch.group('size'))
                        checkFill = False
                    else:
                        # We've reached a new object and no fill in between
                        # Probably the next symbol fills the gap
                        if not re.search(r"\.(bss|text|data|rodata){1}", line):
                            continue

                match = re.search(r"\.(?P<section>(bss|text|data|rodata){1})[\S+|\s+]+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+/src/(?P<module>\S+).o)", line)

                if match:
                    addToModule(modules, match.group('module'), match.group('section'), match.group('size'))
                    # Lets check if the symbol needs filling
                    if ( ((int(match.group('size'), base=16)) % 4 ) != 0):
                        checkFill = True

                else:
                    if re.search(r"^\s\.(bss|text|data|rodata){1}[\S+|\s+]+\n", line):
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

        if args.plotType == 'matplot':
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
        
        if args.plotType == 'plotly':
            xAxis = []
            heightBss = list()
            heightText = list()
            heightData = list()
            heightRodata = list()
            for key in modules.keys():
                for fil in modules[key].values():
                    heightBss.append(fil.bssSize)
                    heightText.append(fil.textSize)
                    heightData.append(fil.dataSize)
                    heightRodata.append(fil.rodataSize)
                    xAxis.append(fil.name)

            xAxis = sorted(xAxis)

            fig = go.Figure(data=[
                go.Bar(name='.bss', x=xAxis, y=heightBss),
                go.Bar(name='.text', x=xAxis, y=heightText),
                go.Bar(name='.data', x=xAxis, y=heightData),
                go.Bar(name='.rodata', x=xAxis, y=heightRodata)
            ])
            
            # Change the bar mode and set labels
            fig.update_layout(
                barmode='stack',
                yaxis_title="Bytes (B)",
                xaxis_title="Module",
                legend_title="Memory Sections",
                hovermode='x',
                title={
                    'text': "Memory usage per module",
                    #'y':0.9,
                    'x':0.5,
                    'xanchor': 'center',
                    'yanchor': 'top'
                    },
                title_font_size=24
            )
                
            fig.show()

    except IOError as msg:
        parser.error(str(msg))
