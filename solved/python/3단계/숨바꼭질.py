from collections import deque
n, k = map(int,input().split())

distance = [0] * 100001
def bfs(start):
  if start == k:
    return
  queue = deque([start])
  while queue:
    v = queue.popleft()
    for i in (v-1,v+1,v*2):
      if(0<=i<=100000 and distance[i] == 0):
        distance[i] = distance[v] + 1
        queue.append(i)
        if i == k:
          return
bfs(n)
print(distance[k])

