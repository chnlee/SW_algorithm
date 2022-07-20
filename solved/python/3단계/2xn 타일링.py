import sys
sys.setrecursionlimit(2000)

d = [0] * 1001

def fibo(n):
  if d[n] != 0:
    return d[n]
  if n==1:
    d[1] = 1
    return d[n]
  elif n==2:
    d[2] = 2
    return d[n]
  else:
    d[n] = fibo(n-1) + fibo(n-2)
    return d[n]

a = int(input())
print(fibo(a)%10007)