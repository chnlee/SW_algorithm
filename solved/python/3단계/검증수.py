a = map(int,input().split())
b = list(map(lambda x : x**2, list(a)))
print(sum(b)%10)