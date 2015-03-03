# -*- coding: utf-8 -*-
"""
Created on Tue Feb 24 20:35:39 2015

@author: laurenmusso
"""
#!/usr/bin/python3


def main():
    fh = open('dynadeck.txt')
    lines = fh.readlines()
    c = 0
    d = 0
    while c < 1:
        for lines in fh:
            if 'CONTROL_TERMINATION' in lines:
                c = 1
            else:
                c = 0
            d += 1
    split_line = lines[d+1].split(",")
    termination_time = split_line[0]
    print(termination_time)
        
if __name__ == "__main__": main()