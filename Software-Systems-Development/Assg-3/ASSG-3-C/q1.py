import json


def readFile(data):
	
	##parent={}
	##level={}
	n=len(data)
	for i in range(1,n):
		for j in data['L'+str(i)]:
			level[j['name']]=i
			parent[j['name']]=j['parent']
	parent[data['L0'][0]['name']]='-1'
	level[data['L0'][0]['name']]=0
	#print(parent)
	#print(level)

def process():
	for element in elements:
		a=element
		aa=a
		if(root==a):
			print("NO LEADER")
			exit()
		aa=[]		
		aa.insert(0,a)
		while(parent[a]!="-1"):
			aa.insert(0,parent[a])
			#aa=parent[a]+aa
			a=parent[a]
		paths.append(aa)

def solve(lca, n):
	
	for path in paths:
		n=min(n,len(path))
	#print(n,m)
	flag=0
	for i in range(0,n):
		prev=lca
		lca=paths[0][i]
		for j in range(1,m):
			if(lca != paths[j][i]):
				flag=1
				break
		if(flag==1):
			break
	return prev

f = open("org.json").read()
f=f.replace("\n","")
data = json.loads(f)
parent={}
level={}
readFile(data)

root=data['L0'][0]['name']

paths=[]
str=input()
tmp=str.split(' ')
m=int(tmp[0])
elements=tmp[1:]
#elements=str.split(' ')
#m=len(elements)


process()

#for i in paths:
#	print(i)
lca='.'
n=99999

lca = solve(lca, n)
		
#lca=prev
print("common leader: ",lca)

#print("level leader - ",level[lca])
for ele in elements:
	print("leader",lca,"is",level[ele]-level[lca],"level above employee",ele)