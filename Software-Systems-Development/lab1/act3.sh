#!/bin/bash
cal > out1.txt
date +'%Y-%m-%d' >> out1.txt
cat cal.txt
sed -n '7,$p' out1.txt
sed -n '3,7p' out1.txt
cat cal.txt | wc -l
touch out2.txt ; echo "The day is awesome" > out2.txt
wc -w out2.txt | awk {'print $1'} 
echo "I am looking forward to the day." >> out2.txt
wc -l out2.txt | awk {'print $1'}
awk '{print $5}' out1.txt
cut -d ' ' -f4,5,6,7 cal.txt
cut -d ' ' -f3,4,5,6,7 cal.txt
cut -d ' ' -f2,4 out2.txt | tr "\n" " "
