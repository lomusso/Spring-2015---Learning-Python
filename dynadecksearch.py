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
        line_number = re.search('CONTROL_TERMINATION', line)
        line_number = line_number+1
        list_one = line_number.split(",")
        model_termination_time = list_one[0]
        print(model_termination_time)
        
        line_number_two = re.search('DATABASE_NODOUT', line)
        line_number_two = line_number_two+1
        list_two = line_number_two.split(",")
        time_step = list_two[0]
        print(time_step)
        
        total_time_steps = (model_termination_time/time_step)+1
        print(total_time_steps)
        
if __name__ == "__main__": main()