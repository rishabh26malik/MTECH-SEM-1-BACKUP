#!/bin/bash
read -p "enter string : " str
#echo $str
len=${#str}
flag=1
l=0
r=`expr $len - 1`
#echo ${str[0]}
flag=1
for (( l=0; l<$len; l++ )); 
do
    ch1=${str:$l:1}	# expands to the substring starting at position $i of length 1.
    ch2=${str:$r:1}
    if [ "$ch1" != "$ch2" ]
    then	
		flag=0
		break
	fi
	r=`expr $r - 1`
    #echo $ch
done

if [ $flag -eq 1 ]
then
	echo "pal"
else
	echo "not pal"
fi