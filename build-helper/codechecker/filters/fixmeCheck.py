#!/usr/bin/env python3

'''
Copyright (C) 2013 Fabian Neuschmidt. All Rights Reserved.
Copyright (C) 2014 Lasse Schuirmann. All Rights Reserved.
Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
'''
import re


def filter(queue, name, lineList):
    """returns error if 'FIXME' is found in the file

    :lineList: file as list of strings
    :returns: all error messages in a list

    """

    errorMessages = [name]

    pattern = re.compile(r"\bFIXME\b")
    for lineNumberMinusOne, line in enumerate(lineList):
        if pattern.search(line):
            errorMessages.append('"FIXME" found in Line {}'.format(lineNumberMinusOne+1))
    queue.put(errorMessages)

