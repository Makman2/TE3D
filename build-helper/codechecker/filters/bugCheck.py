#!/usr/bin/env python3

'''
Copyright (C) 2013 Fabian Neuschmidt. All Rights Reserved.
Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
'''
import re

def filter(queue,name,lineList):
	"""returns error if 'BUG' is found in the file

	:lineList: file as list of strings
	:returns: all error messages in a list

	"""

	errorMessages=[name]

	pattern = re.compile(r"\bBUG\b")
	for lineNumberMinusOne, line in enumerate(lineList):
		if pattern.search(line):
#		if re.search(r"\bBUG\b", line):
			errorMessages.append('"BUG" found in Line {}'.format(lineNumberMinusOne+1))
#	return errorMessages
	queue.put(errorMessages)