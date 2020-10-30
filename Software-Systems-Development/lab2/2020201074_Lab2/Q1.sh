#!/bin/bash
cat file1.txt | tr " " "\n" | grep -i "^s[^a].*"

grep --color -Ei 'work|$' file1.txt  | awk 'BEGIN {IGNORECASE = 1} {if(tolower($3) == "work"){$3="good"} print $0 }' | sed -n '1,$p'

cat file1.txt | awk '
{ 
  split($0, chars, "")
  for (i=1; i <= 4; i++) {
    printf("%s", chars[i])
  }
  for(i=5;i<=length($0);i++){ 
  	printf("#") 
  }
  printf("\n")
}'

awk '{print $4 " " $3 " " $2 " " $1}' file1.txt
