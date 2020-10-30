#!/bin/bash
read str
#echo $str
#str=`echo $str | 'sed s/[()]//g'`
#echo $str
#echo $str | sed 's/[()]/ /g' | sed 's/  */ /g' | sed 's/$[ ]//g' |awk '{print "(" $0 ")"}' 
echo $str | sed 's/[()]/ /g' | xargs | awk '{print "(" $0 ")"}' 