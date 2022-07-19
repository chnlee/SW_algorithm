from sys import stdin

c = set()
num = int(stdin.readline())

for i in range(num):
  a = stdin.readline().split()
  if(a[0]=='add'):
    if(int(a[1]) in c):
      continue
    else:
      c.add(int(a[1]))
  if(a[0]=='remove'):
    if(int(a[1]) in c):
      c.remove(int(a[1]))
    else:
      continue
  if(a[0] == 'check'):
    if(int(a[1]) in c):
      print(1)
    else:
      print(0)
  if(a[0] == 'toggle'):
    if(int(a[1]) in c):
      c.remove(int(a[1]))
    else:
      c.add(int(a[1]))
  if(a[0] == 'all'):
    c = set(range(1,21))
  if(a[0]=='empty'):
    c = set()
