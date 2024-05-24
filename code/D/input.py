from random import randint

n = randint(1, 9)
print(n, randint(1, n))
print(*(randint(1, n) for _ in range(n)))
