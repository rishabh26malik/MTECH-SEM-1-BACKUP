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
		sorted_cmd=`echo ${a[$i]} | grep -o . | sort |tr -d "\n"`
		if [ $sorted_cmd -eq $input ]
		then
			echo $str 
			break
		fi	
	fi
}

