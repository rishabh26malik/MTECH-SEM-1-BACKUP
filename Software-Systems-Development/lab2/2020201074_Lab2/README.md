# SSD LAB 2
## Q1:
`cat file1.txt | tr " " "\n" | grep -i "^s[^a].*"` - This command read file using `cat` command, replaces space with newline & prints each word in separate line. This output is pipelined to grep which prints only those words which start with 's' but are not followed by 'a' using regulare expression `^s[^a].*`

------------------------
## Q2:
  `grep --color -Ei 'work|$' file1.txt  | awk 'BEGIN {IGNORECASE = 1} {if(tolower($3) == "work"){$3="good"} print $0 }' | sed -n '1,$p'` - First part of this command which uses`grep` to highlight all `"work"` in the test irrespective of case. Transfers this output to awk which matches third column value of each line with "work" (using `tolower()` function) outputs entire line using `$0`. This is further pipelined to sed which just displays the input received from awk
  
------------------------
## Q3:
 `cat file1.txt | awk '
{ 
  split($0, chars, "")
  for (i=1; i <= 4; i++) {
    printf("%s", chars[i])
  }
  for(i=5;i<=length($0);i++){ 
  	printf("#") 
  }
  printf("\n")
}'` - AWK read the file line by line, each line is stored in a character array using `split` function. Then a loop is run on each line. Till index=4, exact character is printed and for the rest of characters a `#` is printed in its place. Length of line is extracted using `length()` function where `$0` represents a line.

------------------------
## Q5:
  `awk '{print $4 " " $3 " " $2 " " $1}' file1.txt` - Every line is printed in reverse order by using awk command, `$1` is the value in first column which is printed in last, `$2` is in second column but is printed in 2nd last column in outut and similary for others. AWK command has default field separator as `Blank space` so it need not be explicitly specified.
  
-----------------------
## Github repo link
`https://github.com/rishabh26malik/SSD-Lab-Activity-2`
