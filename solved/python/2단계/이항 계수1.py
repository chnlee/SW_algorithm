def factorial(x):
  n = 1
  for i in range(1,x+1):
    n *= i
  return n

a, b= map(int,input().split())

print(factorial(a)//(factorial(b)*factorial(a-b)))