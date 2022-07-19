from collections import deque
from sys import stdin

c = deque()

def push_back(x):
  c.append(x)
def push_front(x):
  c.appendleft(x)
def pop_front():
  if(len(c)==0):
    print(-1)
  else:
    print(c.popleft())
def pop_back():
  if(len(c)==0):
    print(-1)
  else:
    print(c.pop())
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
  if(a[0]=='push_back'):
    push_back(int(a[1]))
  if(a[0]=='push_front'):
    push_front(int(a[1]))
  if(a[0] == 'pop_front'):
    pop_front()
  if(a[0] == 'pop_back'):
    pop_back()
  if(a[0] == 'size'):
    size()
  if(a[0]=='empty'):
    empty()
  if(a[0]=='front'):
    front()
  if(a[0]=='back'):
    back()