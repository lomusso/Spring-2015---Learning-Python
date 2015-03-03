# -*- coding: utf-8 -*-
"""
Created on Tue Feb 24 20:35:39 2015

@author: laurenmusso
"""
#!/usr/bin/python3

def main():
    fname = 'dynadeck.txt'
    termination_time = extract_time(fname,'CONTROL_TERMINATION')
    time_step = extract_time(fname,'DATABASE_NODOUT')
    print(termination_time,time_step)

def extract_time(fname, keyword):
    """
    return the first word on the next line after keyword in fname
    """
    keyword_found = False

    with open(fname) as f:
        for line in f:
            if keyword_found is True:
                t = line.split(',')[0]
                break
            elif keyword in line:
                keyword_found = True

    return t

if __name__ == "__main__": main()

