n = int(input())

graph = []
blue = 0
white = 0

for i in range(n):
  graph.append(list(map(int,input().split())))
def check(x,y,n):
  global blue, white
  color = graph[x][y]
  for i in range(x, x+n):
    for j in range(y, y+n):
      if color != graph[i][j]:
        check(x,y,n//2)
        check(x,y+n//2,n//2)
        check(x+n//2,y,n//2)
        check(x+n//2,y+n//2,n//2)
        return
  if color == 1:
    blue += 1
  elif color == 0:
    white += 1

      
check(0,0,n)
print(white)
print(blue)