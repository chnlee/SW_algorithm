def prime_number(x):
  for i in range(2,x):
    if (x%i == 0):
      return 0
  return 1
a = int(input())
A = list(map(int,input().split()))
count = 0
for i in range(len(A)):
  if(A[i]>1):
    count += prime_number(A[i])

print(count)
  
  