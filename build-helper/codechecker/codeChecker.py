#!/usr/bin/env python3
'''codeChecker.py

Checks code files by applying filters

Copyright (C) 2013 Fabian Neuschmidt. All Rights Reserved.
Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
'''

import argparse        # processing of arguments
import configparser    # processing of condeChecker.conf
import os        # os interaction
import re        # regular expressions
import sys        # filepath modification
import inspect        # inspection of filter files
import pkgutil        # dynamic import of filters
from collections import OrderedDict #
import multiprocessing

globalArgs = {
    'd': [], 'dd': [], 'f': [], 'ff': [], 't': [], 'i': [], 'c': '', 'v': '',
    'FileFineColor': '',
    'FilePoorColor': '',
    'TextColor': '',
    'VerboseInformationColor': '',
    'WarningColor': ''
}
pass
colorCodes = {
    'black': '0;30', 'bright gray': '0;37',
    'blue': '0;34', 'white': '1;37',
    'green': '0;32', 'bright blue': '1;34',
    'cyan': '0;36', 'bright green': '1;32',
    'red': '0;31', 'bright cyan': '1;36',
    'purple': '0;35', 'bright red': '1;31',
    'yellow': '0;33', 'bright purple': '1;35',
    'dark gray': '1;30', 'bright yellow': '1;33',
    'normal': '0',
}
filterChoices = [ \
    packageName for importer, packageName, _ in
    pkgutil.iter_modules([os.path.realpath(
        os.path.abspath(os.path.join(
            os.path.split(inspect.getfile(inspect.currentframe()))[0],
            "filters")))])]


def printColor(color, *args, end="\n"):
    ''' prints arguments in specified color

    :color: Color in which the folloeing arguments should be printed
    :*args: Any Number of Arguments, preferably strings or numbers
    :returns: None

    '''

    try:
        print('\033[' + colorCodes[globalArgs[color]] + 'm', end='')
        for arg in args:
            print(arg, end=' ')
        print('\033[0m', end=end)
    except:
        for arg in args:
            print(arg, end=' ')
        print("", end=end)


def parseCliArgs():
    ''' parses command line arguments and configures help output.

    :returns: parsed arguments in dictionary structure

    '''

    argparser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=__doc__,
        epilog='''\
    \rPossible choices for filters (-f):
    \r{}
    \r(Default is all)
    '''.format(filterChoices))

    argparser.add_argument('-d', nargs='+', metavar='DIR',
                           help="Directories or files to be checked")
    argparser.add_argument('-dd', nargs='+', metavar='DIR', \
                           help="Directories to be checked including sub-directories")
    argparser.add_argument('-f', nargs='+', metavar='FILTER',
                           choices=filterChoices,
                           help="Filters to be applied")
    argparser.add_argument('-ff', nargs='+', metavar='REGEX',
                           help="regular expressions matching filters to apply")
    argparser.add_argument('-t', nargs='+', metavar='FILETYPE',
                           help="filetypes to be checked")
    argparser.add_argument('-i', nargs='+', metavar='FILETYPE',
                           help="filetypes to be ignored")
    argparser.add_argument('-c', nargs='?', metavar='FILE',
                           default="codeChecker.conf",
                           help="Configuration file")
    argparser.add_argument('-v', action='store_true', help="enable verbosity")
    argVars = vars(argparser.parse_args())
    return argVars


def createConfig(pathToConfig):
    ''' renames configuration file if it exists and creates new configuration file with default values.

    :pathToConfig: Location of configuration File
    :returns: None

    '''

    print('{} seems to be missing or corrupted'.format(pathToConfig))
    try:
        os.rename(pathToConfig, pathToConfig + '.old')
        print('{} backed up as {}'.format(pathToConfig, pathToConfig + '.old'))
    except FileNotFoundError:
        pass
    cfgparser = configparser.ConfigParser()
    cfgparser.optionxform = str        # this makes options case sensitive
    cfgparser['TARGETS'] = OrderedDict([
        ('DefaultTargetLocation', ''),
        ('DefaultRecursiveTargetLocation', ''),
        ('DefaultCheckedFileTypes', ''),
        ('DefaultIgnoredFileTypes', '')
    ])
    cfgparser['FILTERS'] = OrderedDict([
        ('DefaultFilters', ''),
        ('DefaultRegularFilterMatch', '')
    ])
    cfgparser['COLORS'] = OrderedDict([
        ('FileFineColor', 'bright green'),
        ('FilePoorColor', 'bright red'),
        ('TextColor', 'normal'),
        ('VerboseInformationColor', 'cyan'),
        ('WarningColor', 'bright yellow')
    ])
    with open(pathToConfig, 'w') as configfile:
        cfgparser.write(configfile)
        print('created default configuration at {}'.format(pathToConfig))


def parseConfig(pathToConfig):
    """ parses arguments from configuration file

    :returns: parsed arguments in dictionary structure

    """

    cfgparser = configparser.ConfigParser()
    cfgparser.optionxform = str        # this makes options case sensitive
    try:
        assert (os.path.exists(pathToConfig))
        cfgparser.read(pathToConfig)
        confVars = {}
        confVars['d'] = cfgparser['TARGETS']['DefaultTargetLocation'].split(
            ',')
        confVars['dd'] = cfgparser['TARGETS'][
            'DefaultRecursiveTargetLocation'].split(',')
        confVars['f'] = cfgparser['FILTERS']['DefaultFilters'].split(',')
        confVars['ff'] = cfgparser['FILTERS'][
            'DefaultRegularFilterMatch'].split(',')
        confVars['t'] = cfgparser['TARGETS']['DefaultCheckedFileTypes'].split(
            ',')
        confVars['i'] = cfgparser['TARGETS']['DefaultIgnoredFileTypes'].split(
            ',')
        confVars['FileFineColor'] = cfgparser['COLORS']['FileFineColor']
        confVars['FilePoorColor'] = cfgparser['COLORS']['FilePoorColor']
        confVars['TextColor'] = cfgparser['COLORS']['TextColor']
        confVars['VerboseInformationColor'] = cfgparser['COLORS'][
            'VerboseInformationColor']
        confVars['WarningColor'] = cfgparser['COLORS']['WarningColor']
    except(AssertionError, KeyError):
        createConfig(pathToConfig)
        cfgparser.read(pathToConfig)
        confVars = {}
        confVars['d'] = cfgparser['TARGETS']['DefaultTargetLocation'].split(
            ',')
        confVars['dd'] = cfgparser['TARGETS'][
            'DefaultRecursiveTargetLocation'].split(',')
        confVars['f'] = cfgparser['FILTERS']['DefaultFilters'].split(',')
        confVars['ff'] = cfgparser['FILTERS'][
            'DefaultRegularFilterMatch'].split(',')
        confVars['t'] = cfgparser['TARGETS']['DefaultCheckedFileTypes'].split(
            ',')
        confVars['i'] = cfgparser['TARGETS']['DefaultIgnoredFileTypes'].split(
            ',')
        confVars['FileFineColor'] = cfgparser['COLORS']['FileFineColor']
        confVars['FilePoorColor'] = cfgparser['COLORS']['FilePoorColor']
        confVars['TextColor'] = cfgparser['COLORS']['TextColor']
        confVars['VerboseInformationColor'] = cfgparser['COLORS'][
            'VerboseInformationColor']
        confVars['WarningColor'] = cfgparser['COLORS']['WarningColor']

    return confVars


def updateGlobalArgs():
    """ merges configuration options and command line arguments into globalArgs

    :returns: None

    """

    global globalArgs
    argVars = parseCliArgs()
    confVars = parseConfig(argVars['c']) # argVars['c']=location of config file

    # argVars take precedence here
    for arg in ('d', 'dd', 'f', 'ff', 't', 'i'):
        if argVars[arg] == None:
            globalArgs[arg] = confVars[arg]
        else:
            globalArgs[arg] = argVars[arg]

    # if no filter is specified, take all
    if globalArgs['f'] == [''] and globalArgs['ff'] == ['']:
        globalArgs['ff'] = ['.']

    # these can not be specified through confVars


    for arg in ('c', 'v'):
        globalArgs[arg] = argVars[arg]

    # these can not be specified though argVars
    for color in (
        'FileFineColor', 'FilePoorColor', 'TextColor',
        'VerboseInformationColor',
        'WarningColor'):
        globalArgs[color] = confVars[color]

    # cleanup of Values given back by unspecified Arguments in confArgs
    for key in globalArgs.keys():
        if globalArgs[key] == [
            '']:    # while [] and '' are interpreted as False, [''] is True.
            globalArgs[key] = []

    # check filter existence
    for filter in globalArgs['f']:
        if filter not in filterChoices:
            printColor("WarningColor", 'WARNING: The filter',
                       '"' + filter + '"', \
                       'is listed in your configuration file but does not exist!')

    # print verbose Information if -v flag is set
    if globalArgs['v']:
        printColor('VerboseInformationColor', "ARGVARS:", argVars)
        printColor('VerboseInformationColor', "CONFVARS:", confVars)
        printColor('VerboseInformationColor', "GLOBALARGS:", globalArgs)


def listTargetFilePaths():
    """ lists the absolute filepaths of all files that should be checked

    :returns: list of absolute filepaths

    """

    singleLevelDirs = [os.path.abspath(filePath) for filePath in
                       globalArgs['d']] # make them global
    multiLevelDirs = [os.path.abspath(filePath) for filePath in
                      globalArgs['dd']] # make them global
    testedFileTypes = globalArgs['t']
    ignoredFileTypes = globalArgs['i']
    verbosity = globalArgs['v']

    mypath = os.getcwd    # directory from witch the codeChecker is executed
    filePaths = []

    # collect all files from singleLevelDirs
    if singleLevelDirs:
        for dir in singleLevelDirs:
            if verbosity: printColor("VerboseInformationColor",
                                     "NEXT SINGLELEVELDIR:", dir)
            try:
                if os.path.isfile(dir):
                    filePaths.append(dir)
                elif os.path.isdir(dir):
                    filePaths.extend(
                        [os.path.join(dir, file) for file in os.listdir(dir) if
                         os.path.isfile(os.path.join(dir, file))])
                else:
                    printColor("WarningColor", "WARNING:", dir,
                               "is not a valid file or directory and will be ignored!")
            except PermissionError:
                printColor("WarningColor", "WARNING:", dir,
                           "is not accessible and will be ignored")

    def recursiveCollect(dir):
        """recursively collects filenames from directories and all their subdirectories

        :dir: parent directory
        :returns: list of absolute filenames

        """
        tempFilePathList = []
        try:
            for file in os.listdir(dir):
                if os.path.isfile(os.path.join(dir, file)):
                    tempFilePathList.append(os.path.join(dir, file))
                elif os.path.isdir(os.path.join(dir, file)):
                    tempFilePathList.extend(
                        recursiveCollect(os.path.join(dir, file)))
        except PermissionError:
            printColor("WarningColor", "WARNING:", dir,
                       "is not accessible and will be ignored!")
        return tempFilePathList

    # collect all files from multiLevelDirs
    if multiLevelDirs:
        for dir in multiLevelDirs:
            if verbosity: printColor("VerboseInformationColor",
                                     "NEXT MULTILEVELDIR:", dir)
            try:
                if os.path.isfile(dir):
                    filePaths.append(dir)
                if os.path.isdir(dir):
                    filePaths.extend(recursiveCollect(dir))
                else:
                    printColor("WarningColor", "WARNING:", dir,
                               "is not a valid file or directory and will be ignored!")
            except PermissionError:
                printColor("WarningColor", "WARNING:", dir,
                           "is not accessible and will be ignored")

            # remove duplicates and sort
    filePaths = sorted(list(set(filePaths)))
    if verbosity: printColor("VerboseInformationColor",
                             "ALL FILES FROM SINGLE+MULTILEVELDIRS:",
                             filePaths)

    # if '-t' is specified, only test files with given endings
    if testedFileTypes:
        for i in range(len(filePaths) - 1, -1,
                       -1): #backwards to not saw off the branch we're sitting on
            match = 0
            for tFT in testedFileTypes:
                if tFT[0] == '.':
                    tFT = '\\' + tFT        #to escape dots
                if re.search(tFT + '$', filePaths[
                    i]):    #true if filePath ends with fileTypePick
                    match = 1
            if match == 0:
                del filePaths[i]

    # if '-i' is specified, ignore files with given endings
    if ignoredFileTypes:
        if testedFileTypes: ignoredFileTypes = list(
            set(ignoredFileTypes).difference(set(
                testedFileTypes))) # remove all ignoredFileTypes that are also testedFileTypes
        for i in range(len(filePaths) - 1, -1, -1):
            banFilePath = False                        # needed if more than one ban to prevent index errors
            for iFT in ignoredFileTypes:
                if iFT[0] == '.':
                    iFT = '\\' + iFT        #to escape dots
                if re.search(iFT + '$', filePaths[i]):
                    banFilePath = True
            if banFilePath == True:
                del filePaths[i]

    #return list with absolute file paths
    if verbosity: printColor("VerboseInformationColor",
                             "TARGETS FROM SINGLE+MULTILEVELDIRS",
                             str(filePaths))
    return sorted(filePaths)


def collectFilterFunctions():
    """ imports filter functions from filters/ and returns them in a dictionary

    :returns: Dictionary as follows: {NameOfFunction:Function}

    """

    filterNames = globalArgs['f']
    regularFilterMatches = globalArgs['ff']
    verbosity = globalArgs['v']

    filterDict = {}

    #find /codeChecker/filters/ folder independent from current directory
    filtersDirectory = os.path.realpath(os.path.abspath(
        os.path.join(os.path.split(inspect.getfile(inspect.currentframe()))[0],
                     "filters")))
    if verbosity: printColor("VerboseInformationColor", "FILTERSDIRECTORY:",
                             filtersDirectory)
    if filtersDirectory not in sys.path:
        sys.path.insert(0, filtersDirectory)

    # collect Rules according to filterNames and regularFilterMatches:
    for importer, packageName, _ in pkgutil.iter_modules(
            [filtersDirectory]): # all modules in filters/
        useThisFilter = False
        if packageName in filterNames:
            useThisFilter = True
        for regex in regularFilterMatches:
            if re.search(regex, packageName):
                useThisFilter = True
        if useThisFilter == True:
            module = importer.find_module(packageName).load_module(packageName)
            for functionName, function in inspect.getmembers(module):
                if functionName == 'filter':
                    filterDict[packageName] = function
                    if verbosity: printColor('VerboseInformationColor',
                                             "ADDED FILTER:", packageName)
    return filterDict

# MAIN ROUTINE

updateGlobalArgs()
filePathList = listTargetFilePaths()
filterDict = collectFilterFunctions()

# Check all Files in filePathList 
for filePath in filePathList:
    resultList = []
    try:
        with open(filePath, "r") as file:
            lineList = file.readlines()
            resultQueue = multiprocessing.Queue()
            processList = []

            # fill processList with processes
            for filterName, function in filterDict.items():
                processList.append(multiprocessing.Process(target=function,
                                                           args=(resultQueue,
                                                                 filterName,
                                                                 lineList)))

            # start all processes
            for process in processList:
                process.start()

            # collect results if they contain more than the filter name
            for i in range(len(processList)):
                nextQueueItem = resultQueue.get()
                if len(nextQueueItem) > 1: resultList.append(
                    nextQueueItem) # append filterOutputList if it contains more than the filters name

            if not resultList: # File is fine then
                printColor("FileFineColor", filePath, )
            else: # File has errors
                printColor("FilePoorColor", filePath,
                           "({})".format(len(resultList)))
                for filterOutputList in resultList:
                    printColor("TextColor",
                               str(filterOutputList[0]) + "({}):".format(len(
                                   filterOutputList) - 1)) # print filterName and number of messages
                    for outputLineMinusOne in range(len(filterOutputList) - 1):
                        printColor("TextColor", "\t", filterOutputList[
                            outputLineMinusOne + 1]) # print output from that filter

    except UnicodeDecodeError as UDerr: # unable to open file
        printColor("WarningColor", filePath)
        printColor("WarningColor",
                   "WARNING: Unable to read this file: {}".format(UDerr))







