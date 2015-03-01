# -*- coding: utf-8 -*-
"""
Created on Tue Feb 24 20:35:39 2015

@author: laurenmusso
"""
#!/usr/bin/python3

def main():
    with open('dynadeck.txt') as fh:
        c = 0
        d = 0
        while c < 1:
            lines = fh.readlines()
            if 'CONTROL_TERMINATION' in lines:
                c = 1
            else:
                c = 0
            d += 1
        split_line = fh[d+1].split(",")
        termination_time = split_line[0]
        print(termination_time)
        
if __name__ == "__main__": main()