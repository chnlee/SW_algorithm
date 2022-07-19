a = int(input())
b = sorted(list(map(int,input().split())))
c = int(input())
d = list(map(int,input().split()))


n_dic = {}
for i in b:
  if i in n_dic:
    n_dic[i] += 1
  else:
    n_dic[i] = 1

def binary_search(array, target, start, end):
  if start > end:
    return 0
  mid = (start+end)//2
  if array[mid] == target:
    return n_dic.get(target)
  elif array[mid] > target:
    return binary_search(array,target,start, mid-1)
  else:
    return binary_search(array,target,mid+1, end)

for i in range(c):
  result = binary_search(b,d[i],0,c-1)
  print(result, end=" ")