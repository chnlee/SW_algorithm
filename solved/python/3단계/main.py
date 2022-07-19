c = [0] * 41
d = [0] * 41
def fibonacci1(n):
  if(c[n] != 0):
    return c[n]
  if (n ==0):
    c[n] = 1
    return c[n]
  elif(n==1):
    return c[n]
  else:
    c[n] = fibonacci1(n-1) + fibonacci1(n-2)
    return c[n]
def fibonacci2(n):
  if(d[n] != 0):
    return d[n]
  if (n ==0):
    return d[n]
  elif(n==1):
    d[n] = 1
    return d[n]
  else:
    d[n] = fibonacci2(n-1) + fibonacci2(n-2)
    return d[n]
    
n = int(input())

for i in range(n):
  a = int(input())
  print(fibonacci1(a),fibonacci2(a))

  
