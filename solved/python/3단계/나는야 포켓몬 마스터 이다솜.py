from sys import stdin

a, b= map(int,input().split())
name = dict()
num = dict()
for i in range(1,a+1):
  d = stdin.readline().rstrip()
  name[i] = d
  num[d] = i

for i in range(b):
  ans = stdin.readline().rstrip()
  if ans.isdigit():
    print(name[int(ans)])
  else:
    print(num[ans])
    