from sys import stdin

import heapq

hq = []

N = int(input())

for i in range(N):
  a = int(stdin.readline())
  if a>0:
    heapq.heappush(hq,-a)
  else:
    if hq:
      print(-heapq.heappop(hq))
    else:
      print(0)