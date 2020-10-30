### SSD Assignment-2
**1.)**
- Used `json` library for reading json file
- Stored information in json in 2 python dictionaries
- One stores the `child-parent` relationship as key-value pair, other stores `node-level number` as key-value pair
- For finding common leader, I stored path to parent for both nodes in 2 strings. 
- Last common character in 2 string from `left` is the common leader
- **Assumption - Root is assumed to have no parent. So if any of the 2 inputs is root, then no solution is possible in that case.**

**2.)** 
- First dates are processed to get it to a generalized form.
- Days after first date(exclusive) are calculed in that year ... (1)
- Days before second date(exclusive) are calculed in that year ... (2)
- ANSWER = (1) + (2) + #Days in years between the years of 2 dates

**3.)** 
- File is read in a string
- String is processed to extract date and busy time slots.
- Free time slots are calculated for each employee
- **ALL free time slots are converted to minutes and then algorithm is performed.**
- Algorithm is a modification of merge algorithm of merge sort.
- **If dates are not same in 2 files, then "NO FREE SLOT IS AVAILABLE"**
- **In output, slot duration is displayed as floating number, like 0.5 instead of 1/2**