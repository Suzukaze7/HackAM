from random import choice, choices, randint
from string import ascii_lowercase


def rdm(s: str):
    k = randint(0, len(s) - 1)
    c = choice(ascii_lowercase)
    while c == s[k]:
        c = choice(ascii_lowercase)
    return s[:k] + c + s[k + 1:]


n = randint(1, 10)
maxv = int(20)
sz = min(n, maxv // n)
m = maxv // sz

s = ["".join(choices(ascii_lowercase, k=sz)) for _ in range(n)]

print(n, m)
print(*s, sep='\n')
i = j = 0
while j < m:
    while j < m:
        j += 1
        if randint(0, 1):
            print(s[i])
            break
        else:
            k = randint(0, sz - 1)
            print(rdm(s[i]))

    i = (i + 1) % n
