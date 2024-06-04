#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun  3 15:48:09 2024

@author: condo
"""

import csv
import numpy as np
from matplotlib import pyplot as plt

def main():
    
    # opening the 'primarylog' txt file' 
    with open('primarylog.txt', 'r') as f:
        # skipping past the two title lines
       next(f)
       next(f)
       
       # turning the entries into an array
       # removing the newline and spaces between entries
       l = [[int(num) for num in line.strip("\n").split("  ")] for line in f]
       
       #separating the array into two column vectors
       RunNum = [pair[0] for pair in l]
       PrimCount = [pair[1] for pair in l]
    
    
    #scoring volume size
    scoringvols = [i+1 for i in range(20)]
       
    # setting parameters for which files to search through
    filecounter = 0
    countmax = 17
    while filecounter <= countmax:
        mytitle_117 = "output" + str(filecounter) + "_nt_Total Dose.csv"
        mytitle_133 = "output" + str(filecounter + 1) + "_nt_Total Dose.csv"
        
        with open(mytitle_117, newline="") as file_117:
            reader_117 = csv.reader(file_117)
            rows_117 = [line for line in reader_117]
        
        with open(mytitle_133, newline="") as file_133:
            reader_133 = csv.reader(file_133)
            rows_133 = [line for line in reader_133]
            
            
            
        primaries_117 = PrimCount[filecounter]
        rows_117 = rows_117[-1]
        dosedata_117 = np.array([float(val) for val in rows_117])
        dosedata_117 = dosedata_117[1:21]
        
        primaries_133 = PrimCount[filecounter+1]
        rows_133 = rows_133[-1]
        dosedata_133 = np.array([float(val) for val in rows_133])
        dosedata_133 = dosedata_133[1:21]

        tot_dose = dosedata_117 + dosedata_133

        

        totprims = primaries_117 + primaries_133
        #plt.figure(int(filecounter/2 + 1))
        plt.figure(1)
        dpp =  tot_dose/totprims
        
        
        print(dpp[0])
        plt.plot(scoringvols, dpp, ".")
        filecounter += 2
        
        plt.figure(2)
        plt.plot(scoringvols, dosedata_133)
        
    

if __name__ == "__main__":
    main()
