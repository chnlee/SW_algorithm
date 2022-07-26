n = int(input())

a = [[int(x) for x in input().split()] for _ in range(n)]
a.sort(key = lambda x:(x[1],x[0]))
x = 0
count = 1
for i in range(1,n):
  if(a[i][0] >= a[x][1]):
    count += 1
    x = i

print(count)