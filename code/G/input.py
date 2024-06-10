from random import choice, choices, randint
n = randint(1, 10)
q = randint(1, 10)
print(n, q)
print(*[randint(1, 19) for i in range(n)])
for i in range(q):
    l = randint(1, n)
    r = randint(1, n)
    if l > r:
        l, r = r, l
    print(l, r)
