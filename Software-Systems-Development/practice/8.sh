#!/bin/bash
read -p "enter string : " str
case $str in
	[0-9]+) echo "numeric";;
	[a-z]+) echo "alpha";;
	*) echo "else";;
esac