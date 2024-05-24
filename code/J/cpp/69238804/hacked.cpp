n = int(input())
lst = map(int,input().split())
s = 0
for it in lst:
    s = s + it
print(max(0,s-50))