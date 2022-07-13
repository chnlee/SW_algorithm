a = int(input())
for i in range(a):
  count = 1
  b = input()
  if(b[0]==")"):
    print('NO')
    continue
  for i in range(1,len(b)):
    if(b[i] == ")"):
      count -= 1
    else:
      count += 1
    if(count<0):
      break
  if(count==0):
    print('YES')
  else:
    print('NO')