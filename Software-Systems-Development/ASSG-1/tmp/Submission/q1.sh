#!/bin/bash
mkdir Assignment1
cd Assignment1
touch lab{1..5}.txt
find . -name "*.txt" -exec mv {} {}.c\;
rename 's/\.txt/\.c/' *.txt
ls -l | sed 's/  */ /g' | sort -n -k 5
find /home/rishabh -maxdepth 2 -type d,f -ls | sed 's/  */ /g' | awk '{print $11}'
#find /home/rishabh/F/MTECH/Software-Systems-Development/ASSG-1/Assignment1  -name "*.txt"  -ls | sed 's/  */ /g' | awk '{print $11}'


find $(pwd) -name "*.txt" -type f
#When I run find $(pwd), I get list of folders and files with absolute path under current directory