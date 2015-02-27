# -*- coding: utf-8 -*-
"""
Created on Tue Feb 24 20:35:39 2015

@author: laurenmusso
"""
#!/usr/bin/python3

import re

def main():
    fh = open('dynadeck.txt')
    for line in fh:
        match = re.search('CONTROL_TERMINATION', line)
        if match:
            print(match.group())
        match = re.search('DATABASE_NODOUT', line)
        if match:
            print(match.group())

if __name__ == "__main__": main()