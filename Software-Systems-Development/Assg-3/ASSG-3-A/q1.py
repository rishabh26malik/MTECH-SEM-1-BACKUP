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
a=input()
b=input()
aa=a
bb=b
while(parent[a]!="-1"):
	aa=parent[a]+aa
	a=parent[a]
while(parent[b]!="-1"):
	bb=parent[b]+bb
	b=parent[b]
#print(aa,bb)
lca=aa[0]
i=0
j=0
n=len(aa)
m=len(bb)
while(i<n and j<m and aa[i]==bb[j]):
	lca=aa[i]
	i+=1
	j+=1
print(lca,", level - ",level[lca])
