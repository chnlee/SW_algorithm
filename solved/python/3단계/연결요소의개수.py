N, M = map(int,input().split())

graph = [ [] for i in range(N+1)]
for i in range(M):
  a, b = map(int,input().split())
  graph[a].append(b)
  graph[b].append(a)

visited = [False] * (N+1)

def dfs(graph,v,visited):
  if len(graph[v])==0:
    return
  visited[v] = True
  for i in graph[v]:
    if visited[i] == False:
      dfs(graph,i,visited)
 
count = 0
for i in range(1,N+1):
  if visited[i]:
    continue
  dfs(graph,i,visited)
  count += 1

print(count)