#!/bin/bash

HISTFILE=~/.bash_history
set -o history
history | tail -n 10 | awk '{print $2}' | sort | uniq -c | awk '{print $2 " " $1}'

#for((i=0;i<$len;i++));
#do
#	echo ${array[$i]}
#done


#array=($(history | tail -n 10))

#array=($(history | sort -n | tail | awk '{$1=""; print $0}' | sed 's/ //g'))
#array=($(ls | sort -n | tail | awk '{print $0}' | sed 's/ //g'))
#array=($(history 10))
#history

#history > his.txt

#history | sort -n | tail | awk '{$1=""; print $0}' | sort | uniq -c


#history 10 | awk '{$1=""; print $0}' | sort | uniq -c

#array=($(history 10 | cut -c 8- | sort | uniq -c))
#echo `history 10 | cut -c 8- | sort | uniq -c`