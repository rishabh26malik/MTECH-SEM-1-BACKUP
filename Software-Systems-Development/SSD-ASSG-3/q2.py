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
	if(YY%100==0 and YY%400==0 ):
			return True
	elif(YY%100!=0 and YY%4==0):
		return True
	return False

def daysBefore(DD,MM,YY):
	days_count=0
	total_days=365
	leaps=0
	i=0
	#for i in range(0,YY):
	while(i<YY):
		if(isLeap(i)==True):
			leaps+=1
		i+=1
	i=0

	while(i<=MM-2):
		days_count+=days[i]
		i+=1
	#days_count=leaps + 365*(YY)+sum(days[:MM])+DD
	days_count+=leaps + 365*(YY)+DD
	if(isLeap(YY)==True and MM > 2):
		days_count+=1
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


file = open('date_calculator.txt', 'r') 
for line in file:
	#line = file.readline()
	line=line.replace("\n","") 
	dates.append(line)
	
file.close()
date1=dates[0][7:]
date2=dates[1][7:]
#print(date1, date2)

#date1=input()
#date2=input()
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

daysB4_1=daysBefore(DD1,MM1,YY1)
daysB4_2=daysBefore(DD2,MM2,YY2)

#print(daysB4_1)
#print(daysB4_2)
#print(abs(daysB4_2-daysB4_1))

ans=(abs(daysB4_2-daysB4_1))

f = open("output.txt", "w")
f.write("Date Difference: "+str(ans)+" Day")
