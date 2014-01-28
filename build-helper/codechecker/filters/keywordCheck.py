#!/usr/bin/env python3

"""
Copyright (C) 2014 Lasse Schuirmann. All Rights Reserved.
Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
Copyright (C) 2013 Fabian Neuschmidt. All Rights Reserved.
Based on work by Fabian Neuschmidt (fabian.neuschmidt@gmail.com)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
"""

__author__ = 'Lasse Schuirmann'

import re

keywords = ["FIXME", "TODO", "BUG"]


def filter(queue, name, lineList):
    """
    returns error if a keyword is found in the file

    :lineList: file as list of strings
    :returns: all error messages in a list
    """
    error_messages = [name]

    pattern = []
    for keyword in keywords:
        pattern.append(re.compile(r"\b{}\b".format(keyword)))

    for line_number, line in enumerate(lineList):
        for pattern_number, p in enumerate(pattern):
            if p.search(line):
                error_messages.append('"{}" found in Line {}'.format(keywords[pattern_number], line_number + 1))

    queue.put(error_messages)

