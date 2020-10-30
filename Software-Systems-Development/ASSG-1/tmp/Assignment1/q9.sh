#!/bin/bash
read n
n=`echo $n | xargs | sed 's/ //g'`
#echo $n
len=`echo $n | wc -c`
len=`expr $len - 1`

for (( i=0; i<$len; i++ )); 
do
	#echo "${n:$i:1}"
	array[$i]=${n:$i:1}
done


for((i=`echo "$len-2" | bc`;i>=0;i-=2));
do
	num=${array[$i]}
	num=`echo "$num*2" | bc`
	if [ $num -gt 9 ]
	then
		num=`expr $num - 9`
	fi
	array[$i]=$num
done

sum=0
for((i=0;i<$len;i++));
do
	sum=`echo "$sum+${array[$i]}" | bc`
done
rem=`echo "$sum%10" | bc`
if [ $rem -eq 0 ]
then
	echo "Valid"
else
	echo "Invalid"
fi 
