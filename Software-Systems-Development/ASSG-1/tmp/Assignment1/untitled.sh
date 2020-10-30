#!/bin/bash
#array=($(history | sort -n | tail | awk '{$1=""; print $0}' | sed 's/ //g'))
#array=($(ls | sort -n | tail | awk '{print $0}' | sed 's/ //g'))
#array=($(history 10))
history
ls
#history > his.txt
#echo ${array[@]}

history | sort -n | tail | awk '{$1=""; print $0}' | sort | uniq -c


history 10 | awk '{$1=""; print $0}' | sort | uniq -c
