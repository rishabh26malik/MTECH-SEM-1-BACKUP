inp=input()
names=inp.split(',')
new_names=[]
new_names=list(filter(lambda name:name[0].isupper(),names))
tot_len=0
for name in new_names:
	tot_len+=len(name)
print(tot_len)
print(new_names)

