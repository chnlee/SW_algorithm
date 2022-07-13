while(1):
  count = 0;
  a = input()
  if(a=='0'):
    break
  for i in range(len(a)):
    if (a[i] != a[len(a)-(i+1)]):
      count += 1
  if(count):
    print("no")
  else:
    print("yes")