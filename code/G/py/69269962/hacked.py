import math
import calendar
import decimal
import sys
import functools
# list.sort(key=functools.cmp_to_key(lambda a, b: -1 if a<b else 1))
import datetime
import bisect
from collections import Counter


def input():
    return sys.stdin.readline().rstrip()


def ilist():
    return list(map(int, input().split()))


sys.setrecursionlimit(50000007)  # 递归调用的最大深度，默认只有1000
tt = 1
# tt = int(input())


def main():
    n, q = ilist()
    a = ilist()
    assert 1 <= n <= int(2e5)
    assert 1 <= q <= int(2e5)
    assert len(a) == n

    up = [i for i in range(n)]
    id = dict()
    LG = int(math.log2(n))
    lg = [0]*(n+1)
    f = [[0]*(LG+1) for i in range(n)]
    for i in range(n):
        assert 1 <= a[i] <= int(1e9)
        if i and a[i-1] >= a[i]:
            up[i] = up[i-1]
        if id.get(a[i]):
            id[a[i]].append(i)
        else:
            id[a[i]] = [i]
        f[i][0] = i
        lg[i+1] = int(math.log2(i+1))

    for k in range(1, LG+1):
        for i in range(max(0, n-(1 << k)+1)):
            x = f[i][k-1]
            y = f[i+(1 << k-1)][k-1]
            f[i][k] = x if a[x] <= a[y] else y

    def get_id(l, r):
        k = lg[r-l+1]
        i = f[l][k]
        j = f[r-(1 << k)+1][k]
        return i if a[i] <= a[j] else j

    def count_val(val, l, r):
        return bisect.bisect(id[val], r)-bisect.bisect(id[val], l-1)

    def partition_point(l, r, check):
        ans = l
        while l <= r:
            mid = (l+r)//2
            if check(a[mid]):
                l = mid+1
            else:
                ans = mid
                r = mid-1
        return ans

    for i in range(q):
        l, r = ilist()
        assert 1 <= l <= r <= n
        l -= 1
        r -= 1
        p = get_id(l, r)
        if up[r] <= p:
            u = max(l, up[p])
            if u == l:
                print('0')
                continue
            i0 = get_id(l, u-1)
            k = partition_point(u, p, lambda x: x > a[i0])
            print(r-l+1-(count_val(a[i0], l, u-1) + (r-k+1)))
        else:
            print(r-l+1-count_val(a[p], l, r))


for t in range(tt):
    main()

# local Slowest: 4478 ms
# hnist oj : 3576 ms
