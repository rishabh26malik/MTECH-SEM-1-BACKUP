### SSD ASSIGNMENT 1

**1.)** ASSUMPTION - Working directory path is **/home/rishabh/F/MTECH/Software-Systems-Development/ASSG-1/Assignment1**
- `mkdir` is used to create directory, `cd` is used to change current working directory
- `touch lab{1..5}.txt` is used to create multiple files with similar names in a shortcut manner
- `rename 's/\.txt/\.c/' *.txt` is used to rename all .txt files to .c files using pattern matching4
- `ls -l | sed 's/  */ /g' | sort -n -k 5` displays files in isorted file size order. `sed` is used to replace multiple spaces with single space so that it can be used as a separater. Then we sort it on the basis of `Kth` column. Here `k=5` as 5th column has file size
- `find /home/rishabh -maxdepth 2 -type d,f -ls | sed 's/  */ /g' | awk '{print $11}'` is used to display all files in `/home` upto 2 level in hierarchy. `maxdepth 2` sets depth upto 2. `type d,f` ensure both file and directories are displayed. `-ls` is the input to `find` command. `sed 's/  */ /g'` is used to replace multiple spaces with single space so that it can be used as a separater. `awk '{print $11}'` displays the 11th column which contain file path. 

**2.)** Following are the steps followed to solve this question
- First sort the input scrambled word
- Store all commands available in an array
- Now traverse each command and check if it's length is same as input word
- If yes,then compare the sorted input and and sorted command, if they are equal print the command as stop 

**4.)** Following are the 4 steps used in code :
`echo $str - ` display the list with brackets 
`sed 's/[()]/ /g' - ` replace parenthesis with blank space
`xargs - ` remove all multiple blank spaces with a single space
`awk '{print "(" $0 ")"}' - ` append opening parenthesis at the beginning and closing parenthesis at the end
- Above 4 commands are pipelined one after another in sequence to produce appropriate result

**5.)** Standard 2 pointer algorithm is used to check palindrome
- First converted entire string to lowercase using `echo $str | tr "[:upper:]" "[:lower:]"`
- Then followed the 2 pointer algorithm to check palindrome.

**6.)**  `bc` command is used to perform calculation
- First operation is done for 1st two operands
- Then iteratively it is done for rest of the operands

**7.)**
`ps au | awk '(NR>1){print $2}' | sort -n` command is used to extract sorted list of PIDs of currently running processes.
- `ps au` gives details of all process along with their PID in column 2.
- `awk '(NR>1){print $2}'` is used to skip the first row as it contains column titles and `$2` is used to output just column 2 which has PIDs
- `sort -n` sorts the PIDs where `-n` is used to sort as numbers
- Sorted output of above command is stored in an array
- Then first `n` elements are printed where n is input from user

**8.)** File path is `/home/rishabh/F/MTECH/Software-Systems-Development/ASSG-1/crontab_file.txt`
- `$line  > /dev/null 2>&1 ` is used to redirect it to /dev/null so that it is not displayed on terminal
- `$?` is used to check exit status of the command run to know if it executed properly or not 

**9.)** 
- Remove spaces from input using `echo $n | xargs | sed 's/ //g'`
- Calculated length of new string using `echo $n | wc -c`
- Stored element at each index in string in an array iteratively. Element at it
h index is accessed using `{n:$i:1}`, where n is input without spaces
- Then every 2nd digit is traversed from right to left in array, its doubled and if its greater than 9 than we subtract 9 from it
- We now have the new updated number
- Now we sum all numbers in array andthen check its modulus with 10

**10.)** `bc` command is used for performing calculation
- For division precision of 2 is set using `scale` option in the `bc` command
- `Switch case` is used for selecting the operation to be performed
- Result is initialized with first operand.
