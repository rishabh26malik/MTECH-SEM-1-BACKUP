import json

f = open("org.json").read()
f=f.replace("\n","")
data = json.loads(f)
parent={}
level={}
n=len(data)
for i in range(1,n):
	for j in data['L'+str(i)]:
		level[j['name']]=i
		parent[j['name']]=j['parent']
parent[data['L0'][0]['name']]='-1'
level[data['L0'][0]['name']]=0
#print(parent)
#print(level)

root=data['L0'][0]['name']
a=input()
b=input()
aa=a
bb=b

if(root==a or root==b):
	print("NO LEADER")
	exit()
aa=[]
bb=[]
aa.insert(0,a)
aa.insert(0,b)
while(parent[a]!="-1"):
	aa.insert(0,parent[a])
	#aa=parent[a]+aa
	a=parent[a]

while(parent[b]!="-1"):
	bb.insert(0,parent[b])
	#aa=parent[a]+aa
	b=parent[b]

lca=aa[0]
#print(aa)
#print(bb)
i=0
j=0
n=len(aa)
m=len(bb)
while(i<n and j<m and aa[i]==bb[j]):
	lca=aa[i]
	i+=1
	j+=1
print(lca)
print("level of leader - ",level[lca])
