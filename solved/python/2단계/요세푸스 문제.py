from queue import Queue
a, b = map(int,input().split())

c = Queue()

for i in range(1,a+1):
  c.put(i)

print('<',end='')
for i in range(a):
  count = 1
  for i in range(b):
    item = c.get()
    if(count != b):
      c.put(item)
    else:
      if(c.qsize() >=1):
        print(item, end = ', ')
      else:
        print(item, end = '')
        print('>')
    count += 1
  
      

  
  