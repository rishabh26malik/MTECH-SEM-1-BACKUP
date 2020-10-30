days=[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
months = {
  "Jan": 1,   "Feb": 2,
  "Mar": 3,   "Apr": 4,
  "May": 5,   "Jun": 6,
  "Jul": 7,   "Aug": 8,
  "Sep": 9,   "Oct": 10,
  "Nov": 11,  "Dec": 12
}

DD1=0
MM1=0
YY1=0
DD2=0
MM2=0
YY2=0

def isLeap(YY):
	if(YY%100==0):
		if(YY%400==0):
			return True
	elif(YY%4==0):
		return True
	return False

def daysBefore(DD,MM,YY):
	days_count=0
	total_days=365
	if(isLeap(YY)==True):
		days_count+=1
	MM-=1
	i=MM-1
	while(i>=0):
		days_count+=days[i]
		i-=1
	days_count+=DD-1	
	return days_count

def daysAfter(DD,MM,YY):
	days_count=0
	total_days=365
	#if(isLeap(YY)==True):
	#	days_count+=1
	MM-=1
	i=MM+1
	
	while(i<=11):
		days_count+=days[i]
		i+=1
	days_count+=days[MM-1]-DD
	return days_count

def processDate(date):
	if(len(date)==10):
		DD=int(date[0:2])
		MM=int(date[3:5])
		YY=int(date[6:10])
	elif(len(date)==14):
		DD=int(date[0:2])
		MM=months[date[5:8]]
		YY=int(date[10:14])
	else:
		DD=int(date[0:2])
		MM=int(months[date[5:8]])
		YY=int(date[-4:])
	return [DD,MM,YY]

dates=[]
'''
with open("date_calculator.txt") as fp: 
    Lines = fp.readlines()
print(Lines)
'''
'''
file = open('date_calculator.txt', 'r') 
for line in file:
	#line = file.readline()
	line=line.replace("\n","") 
	dates.append(line)
	
file.close()
date1=dates[0][7:]
date2=dates[1][7:]
print(date1, date2)
'''
date1=input()
date2=input()
#exit()
a=processDate(date1)
b=processDate(date2)
DD1=a[0]
MM1=a[1]
YY1=a[2]
DD2=b[0]
MM2=b[1]
YY2=b[2]
#print(DD1,MM1,YY1)
#print(DD2,MM2,YY2)

daysB4=daysBefore(DD1,MM1,YY1)
days_after=daysAfter(DD2,MM2,YY2)
print(daysB4)
print(days_after)
ans=0
if(YY1==YY2):
	if(isLeap(YY1)==True):
		ans=366-daysB4-days_after
	else:
		ans=365-daysB4-days_after
	if(MM1==MM2):
		ans-=2
elif(YY1==YY2-1):
	
	if(isLeap(YY1)==True):
		ans+=(366-daysB4)
	else:
		ans+=(365-daysB4)
	if(isLeap(YY2)==True):
		ans+=(366-days_after)
	else:
		ans+=(365-days_after)
else:
	year=YY1+1
	while(year<YY2):
		ans+=365
		if(isLeap(year)==True):
			ans+=1
		year+=1
	if(isLeap(YY1)==True):
		ans+=(366-daysB4)
	else:
		ans+=(365-daysB4)
	if(isLeap(YY2)==True):
		ans+=(366-days_after)
	else:
		ans+=(365-days_after)
print(ans)
f = open("output.txt", "w")
f.write("Date Difference: "+str(ans)+" Day")