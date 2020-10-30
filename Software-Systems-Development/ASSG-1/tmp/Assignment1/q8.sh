#!/bin/bash

input="/home/rishabh/F/MTECH/Software-Systems-Development/ASSG-1/crontab.txt"
while IFS= read -r line
do
  $line  > /dev/null 2>&1 
  if [ $? -eq 0 ]
  then
	echo "Yes"
  else
	echo "No"
  fi
  #echo "$line"
done < "$input"



#If you don't need the output at all then redirect it to /dev/null

#yourcommand > /dev/null 2>&1