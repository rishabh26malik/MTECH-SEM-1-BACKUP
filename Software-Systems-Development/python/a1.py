import csv
path='/home/rishabh/F/MTECH/Software-Systems-Development/python/weighted_score_date_format.csv'
f=open(path, 'r')
row=csv.reader(f)
header = next(f)
for line in row:
	try:
		part1 = line[2].strip("'")
		part2 = line[3].strip("'")
		partM = int(part1) * float(part2)
	except ValueError as err:
		print("something wrong...",err)
		continue
		print(line)
	#print('First part : ',line[2])
	
	print(partM)
f.close()