a =["WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW"]
b =["BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB"]

num1, num2 = map(int,input().split())
arr = []
for i in range(num1):
  arr.append(input())
min_value = 2500
temp = 0;
for x in range(num1-7):
  for y in range(num2-7):
    count1 = 0;
    count2 = 0;
    for i in range(8):
      for j in range(8):
        if(a[i][j] != arr[x+i][y+j]):
          count1 += 1;
        if(b[i][j] != arr[x+i][y+j]):
          count2 += 1;
    temp = min(count1,count2)
    if(min_value > temp):
      min_value = temp;
          
print(min_value)