from collections import deque
from sys import stdin

c = deque()

def push(x):
  c.append(x)
def pop():
  if(len(c)==0):
    print(-1)
  else:
    print(c.popleft())
def size():
  print(len(c))
def empty():
  if(len(c)==0):
    print(1)
  else:
    print(0)
def front():
  if(len(c)==0):
    print(-1)
  else:
    print(c[0])
def back():
  if(len(c)==0):
    print(-1)
  else:
    print(c[-1])

num = int(stdin.readline())

for i in range(num):
  a = stdin.readline().split()
  if(a[0]=='push'):
    push(int(a[1]))
  if(a[0] == 'pop'):
    pop()
  if(a[0] == 'size'):
    size()
  if(a[0]=='empty'):
    empty()
  if(a[0]=='front'):
    front()
  if(a[0]=='back'):
    back()