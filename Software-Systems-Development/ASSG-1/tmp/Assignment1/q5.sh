#!/bin/bash
read str
#str=`echo str | awk '{print tolower($0)}'`
str=`echo $str | tr "[:upper:]" "[:lower:]"`
#echo $str
len=${#str}
left=0
right=`echo "$len-1" | bc`
while [ $left -lt $right ]
do
	charL=`echo ${str:$left:1}`
	charR=`echo ${str:$right:1}`
	#echo $charL $charR
	if [ "$charL" != "$charR" ]
	then
		echo "No"
		exit
	fi
	left=`echo "$left+1" | bc`
	right=`echo "$right-1" | bc`
done
echo "Yes"
