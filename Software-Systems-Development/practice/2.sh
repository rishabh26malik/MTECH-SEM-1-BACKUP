#!/bin/bash

###  Q-2
if [ $# -eq 2 ]
then
	num1=$1
	num2=$2
	sum=`expr $num1 + $num2`
	echo $sum
else
	echo "wrong no. of args"
fi


###  Q-3

echo `hostname -I | awk '{print $1}'`