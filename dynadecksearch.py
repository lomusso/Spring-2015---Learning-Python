# -*- coding: utf-8 -*-
"""
Created on Tue Feb 24 20:35:39 2015

@author: laurenmusso
"""
#!/usr/bin/python3

import re

def main():
    fh = open('dynadeck.txt')
    c = 0
    d = 0
    while c < 1:
        for line in fh:
            line = fh.readlines()
            if re.search('CONTROL_TERMINATION', line):
                c = 1
            else:
                c = 0
            d += 1
    split_line = fh[d+1].split(",")
    termination_time = split_line[0]
    print(termination_time)
        
if __name__ == "__main__": main()