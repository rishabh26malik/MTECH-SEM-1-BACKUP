'''
from datetime import datetime
s1 = '10:00:00'
s2 = '11:15:00' # for example
FMT = '%H:%M:%S'
tdelta = datetime.strptime(s2, FMT) - datetime.strptime(s1, FMT)
print(tdelta)
'''
import json
#from datetime import datetime
import datetime as dt

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

#print(a)
#exit()

slotLength=float(input())
free1=process(a)
free2=process(b)
print(free1)
print(free2)
freeMin1=inMin(free1)
freeMin2=inMin(free2)
print(freeMin1)
print(freeMin2)
'''
for slot in free2:
	#print(slot[0])
	if(slot[0][0][-2]=='A'):
		time1=slot[0][0][:-2]  #+":00"
		print(time1)
	else:
		i=slot[0][0].find(':')
		#print(slot[0][0][:i])
		time1=str(12+int(slot[0][0][:i]))+slot[0][0][i:-2]  #+":00"
		print(time1)
'''
n=len(freeMin1)
m=len(freeMin2)
i=0
j=0
startIdx="-"
endIdx="-"
slotDur=0
ans=0
slotLength*=60
t=""
while(i<n and j<m):
	slotDur=0
	#print(freeMin1[i], freeMin2[j])
	if(freeMin1[i][0]==freeMin2[j][0]):
		startIdx=free1[i][0]
		slotDur+=freeMin1[i][0]
		#startIdx=freeMin1[i][0]
		if(freeMin1[i][1]==freeMin2[j][1]):
			endIdx==free1[i][1]
			slotDur=freeMin1[i][1]-slotDur
			#endIdx=freeMin1[i][1]
		elif(freeMin1[i][1] < freeMin2[j][1]):
			endIdx=free1[i][1]
			slotDur=freeMin1[i][1]-slotDur
			#endIdx=freeMin1[i][1]
		else:
			endIdx=free2[j][1]
			slotDur=freeMin2[j][1]-slotDur
			#endIdx=freeMin2[j][1]
	
		if(slotLength==slotDur):
			ans=1
			break
		elif(slotLength<slotDur):
			ans=1
			#print(slotLength,freeMin1[i][0])
			endTime=slotLength + freeMin1[i][0] 
			#print(endTime)
			'''
			am_pm=""
			t=""
			hh=int(endTime//60)
			if(hh<12):
				t+=str(hh)+":"
			elif(hh>12):
				t+=str(hh-12)+":"
			t+=str(int(endTime%60))
			if(hh<12):
				t+="AM"
			else:
				t+="PM"
			break
			'''
		i+=1
		j+=1
		'''
		if(slotLength==slotDur):
			ans=1
			break
		'''
	elif(freeMin1[i][1] > freeMin2[j][0] and freeMin1[i][1] < freeMin2[j][1]):
		endIdx=free1[i][1]
		startIdx=free2[j][1]
		slotDur=freeMin2[j][1]-freeMin2[j][1]
		#startIdx=freeMin2[j][1]
		#endIdx=freeMin2[j][1]
		'''
		if(slotLength==slotDur):
			ans=1
			break
		elif(slotLength<slotDur):
			#print(slotLength,freeMin1[i][0])
			ans=1
			endTime=slotLength + freeMin2[j][1] 
			#print(endTime)
			am_pm=""
			t=""
			hh=int(endTime//60)
			if(hh<12):
				t+=str(hh)+":"
			elif(hh>12):
				t+=str(hh-12)+":"
			t+=str(int(endTime%60))
			if(hh<12):
				t+="AM"
			else:
				t+="PM"
			break
		'''
		j+=1

	elif(freeMin1[i][0] > freeMin2[j][0] and freeMin1[i][0] < freeMin2[j][1]):
		endIdx=free2[j][1]
		startIdx=free1[i][0]
		slotDur=freeMin2[j][1]-freeMin1[i][1]
		#startIdx=freeMin1[i][0]
		#endIdx=freeMin2[j][1]
		'''
		if(slotLength==slotDur):
			ans=1
			break
		elif(slotLength<slotDur):
			#print(slotLength,freeMin1[i][0])
			ans=1
			endTime=slotLength + freeMin1[i][0] 
			#print(endTime)
			am_pm=""
			t=""
			hh=int(endTime//60)
			if(hh<12):
				t+=str(hh)+":"
			elif(hh>12):
				t+=str(hh-12)+":"
			t+=str(int(endTime%60))
			if(hh<12):
				t+="AM"
			else:
				t+="PM"
			break
		'''
		i+=1
		'''
		if(slotLength==slotDur):
			ans=1
			break
		'''

	elif(freeMin1[i][0] < freeMin2[j][0] and freeMin1[i][1] > freeMin2[j][1]):
		endIdx=free2[j][1]
		startIdx=free2[j][0]
		slotDur=freeMin2[j][1]-freeMin2[j][1]
		#startIdx=freeMin1[i][0]
		#endIdx=freeMin2[j][1]
		'''
		if(slotLength==slotDur):
			ans=1
			break
		elif(slotLength<slotDur):
			#print(slotLength,freeMin1[i][0])
			ans=1
			endTime=slotLength + freeMin1[i][0] 
			#print(endTime)
			am_pm=""
			t=""
			hh=int(endTime//60)
			if(hh<12):
				t+=str(hh)+":"
			elif(hh>12):
				t+=str(hh-12)+":"
			t+=str(int(endTime%60))
			if(hh<12):
				t+="AM"
			else:
				t+="PM"
			break
		'''
		i+=1

	elif(freeMin2[j][0] < freeMin1[i][0] and freeMin2[j][1] > freeMin1[i][1]):
		endIdx=free1[i][1]
		startIdx=free1[i][0]
		slotDur=freeMin1[i][1]-freeMin1[i][1]
		#startIdx=freeMin1[i][0]
		#endIdx=freeMin2[j][1]
		'''
		if(slotLength==slotDur):
			ans=1
			break
		elif(slotLength<slotDur):
			#print(slotLength,freeMin1[i][0])
			ans=1
			endTime=slotLength + freeMin1[i][0] 
			#print(endTime)
			am_pm=""
			t=""
			hh=int(endTime//60)
			if(hh<12):
				t+=str(hh)+":"
			elif(hh>12):
				t+=str(hh-12)+":"
			t+=str(int(endTime%60))
			if(hh<12):
				t+="AM"
			else:
				t+="PM"
			break
		'''
		j+=1


	elif(freeMin1[i][0] > freeMin2[j][1]):
		i+=1
	elif(freeMin2[j][0] > freeMin1[i][1]):
		j+=1
	
	
available_1=[]
available_2=[]
for slot in free1:
	tmp=slot[0][0]+"-"+slot[1][0]
	available_1.append(tmp)
for slot in free2:
	tmp=slot[0][0]+"-"+slot[1][0]
	available_2.append(tmp)
print(available_1)
print(available_2)
print(startIdx, t, slotDur/60, ans)

