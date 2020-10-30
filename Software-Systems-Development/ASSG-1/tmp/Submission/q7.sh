#!/bin/bash
#array=($(ps ax | awk '(NR>1){print $1}' | sort -n | sed -n '1,$p' | sort -n))
array=($(ps au | awk '(NR>1){print $2}' | sort -n))
echo "${array[*]}" > pid.txt
read n
len=${#array[@]}
if [ $n -gt $len ]
then
	n=$len
fi
for((i=0;i<n;i++));
do
	echo ${array[$i]}
done
# ps ax | awk '(NR>1){print $1}' | sort -n | sed -n '1,10p'
