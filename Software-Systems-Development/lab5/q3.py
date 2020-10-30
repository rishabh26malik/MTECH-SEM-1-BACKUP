def func(word):
	return len(word)
inp=input()
words=inp.split(',')
out=map(func,words)
arr=list(out)
print(arr)
