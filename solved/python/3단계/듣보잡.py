a, b = map(int,input().split())

d = set()
e = set()
for i in range(a):
  name = input()
  d.add(name)
for i in range(b):
  name = input()
  e.add(name)

set3 = d & e

print(len(set3))
new_set = sorted(set3)

for i in range(len(set3)):
  print(new_set[i])