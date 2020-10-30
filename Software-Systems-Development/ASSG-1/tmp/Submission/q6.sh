#!/bin/bash
len=$#
#echo $len
res=`echo "$1^$2" | bc`
i=0
for var in "$@"
do
    if [ $i -ge 2 ]
    then
    	res=`echo "$res^$var" | bc` 	
    fi
    i=`echo "$i+1" | bc`

done
echo $res
