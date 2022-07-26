n, r, c = map(int, input().split())
ans = 0
while n != 0:
  if r < 2**(n-1) and c < 2**(n-1):
    ans += 0
  elif r < 2**(n-1) and c >= 2**(n-1):
    ans += 2**(2*n) // 4
    c -= 2**(n-1)
  elif r >= 2**(n-1) and c < 2**(n-1):
    ans += (2**(2*n) // 4) * 2
    r -= 2**(n-1)
  else:
    ans += (2**(2*n) // 4) * 3
    r -= 2**(n-1)
    c -= 2**(n-1)
  n -= 1
  
print(ans)