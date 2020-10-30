#!/bin/bash
#mkdir Assignment1
#cd Assignment1
#touch lab{1..5}.txt
#find . -name "*.txt" -exec mv {} {}.c\;
#rename 's/\.txt/\.c/' *.txt
#ls -l | sed 's/  */ /g' | sort -n -k 5
find /home/rishabh/F/MTECH -maxdepth 2 -type d,f -ls | sed 's/  */ /g' | awk '{print $11}'
