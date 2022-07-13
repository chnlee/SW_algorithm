from itertools import combinations

a, b= map(int,input().split())

card = list(map(int,input().split()))

s = list(combinations(card,3))

count = 0;

for i in range(len(s)):
  if(sum(s[i]) <= b):
    if(count < sum(s[i])):
      count = sum(s[i])

print(count)
  