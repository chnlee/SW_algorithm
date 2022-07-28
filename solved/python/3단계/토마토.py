from collections import deque

m, n = map(int,input().split())

graph = list()

for i in range(n): 
  a = list(map(int,input().split()))
  graph.append(a)



dx = [-1,1,0,0]
dy = [0,0,-1,1]

def bfs():
  queue = deque()
  for j in range(m):
    for i in range(n):
      # 값을 미리 넣어놓는 것이 핵심이다.
      if graph[i][j] == 1:
        queue.append((i,j))
  while queue:
    x, y = queue.popleft()
    for i in range(4):
      nx = x + dx[i]
      ny = y + dy[i]
      if nx < 0 or nx >= n or ny < 0 or ny >= m:
        continue
      if graph[nx][ny] == 0:
        graph[nx][ny] = graph[x][y] + 1
        queue.append((nx,ny))
    


ans = 0

bfs()

for i in graph:
  for j in i:
    if j == 0:
      print(-1)
      exit()
    ans = max(ans,max(i))
    
print(ans-1)


    