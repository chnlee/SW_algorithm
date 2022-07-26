d = [0] * 11

def fibo(n):
  if d[n] != 0:
    return d[n]
  if n == 1:
    d[1] = 1
    return d[n]
  elif n==2:
    d[2] = 2
    return d[n]
  elif n==3:
    d[3] = 4
    return d[n]
  else:
    d[n] = fibo(n-3)+fibo(n-2)+fibo(n-1)
    return d[n]

T = int(input())
for i in range(T):
  a = int(input())
  print(fibo(a))