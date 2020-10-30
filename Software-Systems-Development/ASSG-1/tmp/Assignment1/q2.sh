#!/bin/bash
read input
len=${#input}
arr=`compgen -c`
#echo $str
input=`echo $input | grep -o . | sort |tr -d "\n"`

a=($(echo $arr | tr " " "\n"))
#echo ${#a[@]}
n=${#a[@]}
cmd=[]
sorted=[]
j=0;
for((i=0;i<$n;i++)){
	str=${a[$i]}
	if [ ${#str} -eq $len ]
	then
		cmd[$j]=${a[$i]}
		sorted[$j]=`echo ${a[$i]} | grep -o . | sort |tr -d "\n"`
		j=`echo "$j+1" | bc`
	fi
}
#echo cba | grep -o . | sort |tr -d "\n"
for((i=0;i<$j;i++)){
	if [ $input == ${sorted[$i]} ]
	then
		echo ${cmd[$i]} 
		break
	fi
	#echo ${cmd[$i]} " " ${sorted[$i]} 
}
