import queue
dx = (0, 1, 0, -1)
dy = (1, 0, -1, 0)
n, m = list(map(int, input().split()))


def toId(i, j):
    return i*m+j


a = [input() for i in range(n)]
assert 4 <= n <= 1000
assert 4 <= m <= 1000
assert len(a) == n
for i in range(n):
    assert len(a[i]) == m
    if i == 0 or i == n-1:
        assert all(x == '#' for x in a[i])
    else:
        assert a[i][0] == '#' and a[i][-1] == '#'

s = -1
t = -1
nxt = [[-1]*4 for i in range(n*m)]
for i in range(n):
    for j in range(m):
        if a[i][j] == '#':
            continue
        u = toId(i, j)
        if a[i][j] == 'S':
            s = u
        if a[i][j] == 'T':
            t = u
        for k in range(4):
            nxt[u][k] = u
        if a[i-1][j] != '#':
            nxt[u][3] = nxt[toId(i-1, j)][3]
        if a[i][j-1] != '#':
            nxt[u][2] = nxt[toId(i, j-1)][2]
for i in range(n-1, -1, -1):
    for j in range(m-1, -1, -1):
        if a[i][j] == '#':
            continue
        u = toId(i, j)
        if a[i+1][j] != '#':
            nxt[u][1] = nxt[toId(i+1, j)][1]
        if a[i][j+1] != '#':
            nxt[u][0] = nxt[toId(i, j+1)][0]
assert s != -1
assert t != -1
d = [int(1e9)]*(n*m)
d[s] = 0
q = [0]*(n*m)
qn = 0
q[qn] = s
qn += 1
i = 0
while i < qn:
    u = q[i]
    i += 1
    if u == t:
        print(d[u])
        quit()

    for j in range(4):
        v = nxt[u][j]
        if d[v] > d[u]+1:
            d[v] = d[u]+1
            q[qn] = v
            qn += 1
print(-1)
