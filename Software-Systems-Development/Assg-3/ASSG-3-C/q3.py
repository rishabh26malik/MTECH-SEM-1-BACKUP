import json
import sys

def isDateSame(Data):
	dates={}
	n=len(Data)
	for i in range(1,n):
		a=open(Data[i]).read()
		emp1=a.split(':')	
		date1=emp1[1][3:-1]
		dates[date1]=1
	if(len(dates)==1):
		return date1
	return "False"	


	emp1=a.split(':')
	emp2=b.split(':')
	date1=emp1[1][3:-1]
	date2=emp2[1][3:-1]
	#print(date1, date2)
	if(date1!=date2):
		return "False"
	return date1

def process(empData):
	empData=empData.replace(" ","")
	empData=empData.replace("'","")
	i=empData.find('[')
	#print(empData[i+1:-3])
	x=empData[i+1:-3].split(',')
	#print(x)
	emp1=[]
	for t in x:
		emp1.append(t.split('-'))
	#print(emp1)
	free=[]
	start="9:00AM"
	for slot in emp1:
		if(slot[0] != start):
			free.append([[start],[slot[0]]])
		start=slot[1]
	if(start != "5:00PM"):
		free.append([[start],["5:00PM"]])
	#print(free)
	return free

def inMin(free):
	freeMin=[]
	for slot in free:
		tmp=slot[0][0].split(':')
		if(slot[0][0][-2]=='A'):
			start=int(tmp[0])*60 + int(tmp[1][:-2])		
		else:
			if(tmp[0]!="12"):
				start=(int(tmp[0])+12)*60 + int(tmp[1][:-2])
			else:
				start=int(tmp[0])*60 + int(tmp[1][:-2])	
		#print(tmp, start)
		tmp=slot[1][0].split(':')
		#print(tmp)
		if(slot[1][0][-2]=='A'):
			end=int(tmp[0])*60 + int(tmp[1][:-2])		
		else:
			if(tmp[0]!="12"):
				end=(int(tmp[0])+12)*60 + int(tmp[1][:-2])
			else:
				end=int(tmp[0])*60 + int(tmp[1][:-2])
		freeMin.append([start,end])
	return freeMin

def getName(data):
	tmp=data.split(':')
	#print(tmp)
	return tmp[0][2:-1]

n=len(sys.argv)
freeMin=[]
available=[]
free=[]
Emp=[]
for i in range(1,n):
	a=open(sys.argv[i], 'r').read()
	a=a.replace("\n","")
	#print(a)
	free1=process(a)
	free.append(free1)
	available_1=[]
	freeMin1=inMin(free1)
	freeMin.append(freeMin1)

	for slot in free1:
		tmp=slot[0][0]+"-"+slot[1][0]
		available_1.append(tmp)
	available.append(available_1)

	ava1=[]
	
	for it in available_1:
		ava1.append("'"+it+"'")
	Emp1=", ".join(ava1)	
	name=getName(a)
	emp1=name+": ["+Emp1+"]\n"
	Emp.append(emp1)

f = open("output.txt", "w")
f.write("Available slot\n")
for i in Emp:
	f.write(i)
slotLength=float(input())
check=isDateSame(sys.argv)

if(check!="False"):
	
	end=0
	index=[0]*(n-1)
	#print(index)
	flag=0
	slotDur=0
	ans=0
	slotLength*=60
	m=n-1
	startIdx="-"
	while(True):
		
		for i in range(0,m):
			if(index[i]>=len(freeMin[i])):
				flag=1
				break
		if(flag==1):
			break
		start=0
		for i in range(0,m):
			if(start < freeMin[i][index[i]][0]):
				start=freeMin[i][index[i]][0]
				startIdx=[i,index[i]]
		slotDur=start+slotLength
		flag1=1
		for i in range(0,m):
			if(	slotDur > freeMin[i][index[i]][1]):
				flag1=0
				break
		if(flag1==1):
			end=int(slotDur)
			ans=1
			break

		for i in range(0,m):
			if(slotDur > freeMin[i][index[i]][1]):
				index[i]+=1
		
		slotDur=int(slotDur)
	HH=int(slotDur//60)
	MM=int(slotDur%60)
	if(MM<10):
		MM="0"+str(MM)
	MM=str(MM)
	if(HH<12):
		endTime=str(HH)+":"+(MM)+"AM"
	elif(HH==12):
		endTime=str(HH)+":"+(MM)+"PM"
	else:
		HH=HH-12
		endTime=str(HH)+":"+(MM)+"PM"
	freeSlot=free[startIdx[0]][startIdx[1]][0][0]+" - "+endTime
	out="{'"+check+"' : ['"+freeSlot+"']}\n"
	slotPrint="Slot Duration:"+str(float(slotLength/60))+" hour\n"

	if(ans==1):
		f.write(slotPrint)
		f.write(out)
	else:
		f.write("No free slot available")
else:
	f.write("No free slot available")
f.close()

