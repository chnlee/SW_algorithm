v = map(int,input().split())
b = list(map(lambda x : x**2, list(v)))
print(sum(b)%10)
