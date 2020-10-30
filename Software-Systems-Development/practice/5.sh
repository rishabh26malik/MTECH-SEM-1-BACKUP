#!/bin/bash
a=0
b=1
val=`expr $a + $b`
n=100
while [ $val -le $n ]
do
	echo $val
	val=`expr $a + $b`
	a=$b
	b=$val
done