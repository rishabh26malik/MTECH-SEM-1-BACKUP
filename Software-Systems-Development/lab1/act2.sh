#!/bin/bash
cat hamlet.txt | tr " " "\n" | grep -ioc 'to'
grep -i ' is ' hamlet.txt
grep -i -A 2 ' bear ' hamlet.txt
chmod go-rwx hamlet.txt
chmod -077 hamlet.txt
chmod +777 hamlet.txt
groups

ls -l |sed -n  '/-[r-][w-][x-][r-][w-][x-][r-][w-]x/p' | awk '{print $9}'