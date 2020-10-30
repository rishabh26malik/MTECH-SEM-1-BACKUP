import json

def isDateSame(a,b):
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

#a="{'Employee1': {'5/10/2020':['10:00AM - 11:00AM', '12:30PM - 1:00PM', '4:00PM - 5:00PM']}}"
#b="{'Employee2': {'5/10/2020':['10:30AM - 11:30AM', '12:00PM - 1:00PM', '1:00PM - 1:30PM','3:30PM - 4:30PM']}}"
a = open('Employee1.txt', 'r').read()
b = open('Employee2.txt', 'r').read()
#print(a)
a=a.replace("\n","")
b=b.replace("\n","")

slotLength=float(input())
free1=process(a)
free2=process(b)
#print(free1)
#print(free2)
freeMin1=inMin(free1)
freeMin2=inMin(free2)
#print(freeMin1)
#print(freeMin2)

available_1=[]
available_2=[]
for slot in free1:
	tmp=slot[0][0]+"-"+slot[1][0]
	available_1.append(tmp)
for slot in free2:
	tmp=slot[0][0]+"-"+slot[1][0]
	available_2.append(tmp)
#print(available_1)
#print(available_2)

ava1=[]
ava2=[]
for it in available_1:
	ava1.append("'"+it+"'")
for it in available_2:
	ava2.append("'"+it+"'")
Emp1=", ".join(ava1)	
emp1="Employee1: ["+Emp1+"]\n"
#print(emp1)
Emp2=", ".join(ava2)	
emp2="Employee2: ["+Emp2+"]\n"
#print(emp2)
#freeSlot=startIdx[0]+" - "+endTime
#out="{'"+check+"' : ['"+freeSlot+"']}\n"

f = open("output.txt", "w")
f.write("Available slot\n")
f.write(emp1)
f.write(emp2)


check=isDateSame(a,b)
if(check!="False"):
	n=len(freeMin1)
	m=len(freeMin2)
	i=0
	j=0
	startIdx="-"
	slotDur=0
	ans=0
	slotLength*=60
	while(i<n and j<m):
		start=max(freeMin1[i][0], freeMin2[j][0])
		startIdx=free1[i][0] if(freeMin1[i][0] > freeMin2[j][0]) else free2[j][0]
		slotDur=start+slotLength
		if(	slotDur<=freeMin1[i][1] and slotDur<=freeMin2[j][1] ):
			end=slotDur
			ans=1
			break

		if(slotDur > freeMin1[i][1]):
			i+=1
		if(slotDur > freeMin2[j][1]):
			j+=1
	slotDur=int(slotDur)
	#print(startIdx,start, slotDur, ans)
	HH=int(slotDur//60)
	MM=int(slotDur%60)
	if(HH<12):
		endTime=str(HH)+":"+str(MM)+"AM"
	elif(HH==12):
		endTime=str(HH)+":"+str(MM)+"PM"
	else:
		HH=HH-12
		endTime=str(HH)+":"+str(MM)+"PM"
	freeSlot=startIdx[0]+" - "+endTime
	out="{'"+check+"' : ['"+freeSlot+"']}\n"
	slotPrint="Slot Duration:"+str(float(slotLength/60))+" hour\n"
	f.write(slotPrint)
	f.write(out)
else:
	#print("No free slot available")
	f.write("No free slot available")
f.close()
