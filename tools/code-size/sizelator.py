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
from plotly.subplots import make_subplots
from prettytable import PrettyTable
import pandas as pd

class FileObj:
    textSize = 0
    rodataSize = 0
    dataSize = 0
    bssSize = 0
    name = ''

    def __init__(self, name):
        self.name = name

    def addBss(self, value):
        self.bssSize += value

    def addText(self, value):
        self.textSize += value

    def addData(self, value):
        self.dataSize += value

    def addRoData(self, value):
        self.rodataSize += value

    def add(self, section, value):
        switcher = {
        'bss': self.addBss,
        'text': self.addText,
        'data': self.addData,
        'rodata': self.addRoData
        }
        func = switcher.get(section)
        func(value)
        
class Symbol:
    module = ''
    size = 0
    section = ''

    def __init__(self):
        self.module = ''
        self.size = 0
        self.section = ''
    
    def purge(self):
        self.module = ''
        self.size = 0
        self.section = ''


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

def addSymbol():
    addToModule(modules, currentSymbol.module, currentSymbol.section, currentSymbol.size)
    currentSymbol.purge()

def caseWaitSection(state):
    match = re.search(r'^\.(bss|text|rodata|data)\s', line)
    if match:
        state = 'InSection'
    return state

def caseInSection(state):
    if re.search(r"^\n", line):
        state = 'WaitSection'
    else:
        match = re.search(r"\s\.(?P<section>bss|text|rodata|data)[.\w+|\s+]+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+\/src\/(?P<module>\S+).o)", line)
        if match:
            currentSymbol.module = match.group('module')
            currentSymbol.size = (int(match.group('size'), base=16))
            currentSymbol.section = match.group('section')
            state = 'WaitFill'
        else:
            match = re.search(r"\s\.(?P<section>bss|text|rodata|data)[.\w+|\s+]+\n", line)
            if match:
                addSymbol()
                currentSymbol.section = match.group('section')
                state = 'WaitSize'
            else:
                if re.search(r"^\s\*\(COMMON\)", line):
                    state = 'InSubSection'
                else:
                    state = 'InSection'
    return state
            
def caseWaitFill(state):
    match = re.search(r"\s\*fill\*\s+0x\w+\s+(?P<fill>0x[\dabcdef]+)", line)
    if match:
        currentSymbol.size += (int(match.group('fill'), base=16))
        state = 'InSection'
        # Add symbol
        addSymbol()
    else:
        match = re.search(r"\s\.(?P<section>bss|text|rodata|data)[.\w+|\s+]+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+\/src\/(?P<module>\S+).o)", line)
        if match:
            # No fill, add previous symbol
            addSymbol()
            # Store current symbol data
            currentSymbol.module = match.group('module')
            currentSymbol.size = (int(match.group('size'), base=16))
            currentSymbol.section = match.group('section')
            state = 'WaitFill'
        else:
            match = re.search(r"\s\.(?P<section>bss|text|rodata|data)[.\w+|\s+]+\n", line)
            if match:
                # No fill, add previous symbol
                addSymbol()
                state = 'WaitSize'
                currentSymbol.section = match.group('section')
            else:
                if re.search(r"^\s+0x[\dabdcef]+\s+\w+\n", line):
                    # 3 line symbol?
                    pass
                else:
                    state = 'InSection'
    return state
            
def caseWaitSize(state):
    match = re.search(r"^\s+0x[\dabdcef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+/src/(?P<module>\S+).o)", line)
    if match:
        currentSymbol.module = match.group('module')
        currentSymbol.size = (int(match.group('size'), base=16))
        state = 'WaitFill'
    else:
        state = 'InSection'
    return state

def caseInSubSection(state):
    match = re.search(r"^\sCOMMON\s+0x[\dabcdef]+\s+(?P<size>0x[\dabcdef]+)\s(\S+/src/(?P<module>\S+).o)", line)
    if match:
        currentSymbol.section = 'bss' # Hardcoded as this is a forced subsection
        currentSymbol.module = match.group('module')
        currentSymbol.size = (int(match.group('size'), base=16))
        # TODO: Consider FILL
        addSymbol()
    else:
        if re.search(r"^\n", line):
            state = 'WaitSection'
        else:
            state = 'InSubSection'
    return state

if __name__ == "__main__":
    try:
        args = parser.parse_args(sys.argv[1:])

        modules = {'fwk': {}, 'trc': {}, 'tmr': {}, 'sma': {}, 
                   'sm': {}, 'mempool': {}, 'queue': {}}

        for key in modules.keys():
            createFilesDic(modules[key], key)

        print('--------- Parsing objects ---------')

        state = 'WaitSection'
        switch = {}
        switch['WaitSection'] = caseWaitSection
        switch['InSection'] = caseInSection
        switch['WaitFill'] = caseWaitFill
        switch['WaitSize'] = caseWaitSize
        switch['InSubSection'] = caseInSubSection

        currentSymbol = Symbol()

        for line in args.mapFile:
            case = switch.get(state)
            state = case(state)


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
            df = pd.DataFrame({'Module':[],'.bss':[],'.text':[],'.data':[],'.rodata':[]}) #A dataframe is easier to sort than a dictionary

            for key in modules.keys():
                for fil in modules[key].values():
                    df = df.append({
                        'Module':fil.name,
                        '.bss':fil.bssSize,
                        '.text':fil.textSize,
                        '.data':fil.dataSize,
                        '.rodata':fil.rodataSize},
                         ignore_index=True)

            df = df.astype({'Module':str,'.bss':int,'.text':int,'.data':int,'.rodata':int})

            df.sort_values(by='Module',     #column name or index values according to which the dataframe is to be sorted
                     axis=0,                #for column sorting
                     ascending=True,
                     inplace = True
            )

            fig = make_subplots(
                rows=1, cols=2,
                specs=[[{"type": "table"}, {"type": "bar"}]]
                )

            fig.add_trace(
                go.Table(
                    header=dict(
                        values=list(df.columns) #['Module', '.bss', '.text', '.data', '.rodata']
                    ),
                    cells=dict(
                        values=[
                            df.Module,
                            df['.bss'],
                            df['.text'],
                            df['.data'],
                            df['.rodata']
                        ],
                        #line_color='darkslategray',
                        #fill=dict(color=['lightgray']),#, 'white']),
                        align=['left', 'center']
                        #,font_size=12
                        )
                    ),
                row=1, col=1
            )

            fig.add_trace (
                go.Bar(name='.bss', x=df.Module, y=df['.bss']), row=1, col=2
            )
            fig.add_trace (
                go.Bar(name='.text', x=df.Module, y=df['.text']), row=1, col=2
            )
            fig.add_trace (
                go.Bar(name='.data', x=df.Module, y=df['.data']), row=1, col=2
            )
            fig.add_trace (
                go.Bar(name='.rodata', x=df.Module, y=df['.rodata']), row=1, col=2
            )
            
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
            
            fig.write_html("plotlyPlot.html")

            fig.show()
    except IOError as msg:
        parser.error(str(msg))
