from sys import stdin

from queue import PriorityQueue

q = PriorityQueue()

N = int(input())

for i in range(N):
  a = int(stdin.readline())
  if a==0:
    if q.qsize() > 0:
      print(-(q.get()))
    else:
      print(0)
  else:
    q.put(-a)