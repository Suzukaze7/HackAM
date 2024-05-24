import random


def generate_random_matrix(maxn):
    # 随机生成 n 和 m
    n = random.randint(4, maxn)
    m = random.randint(4, maxn)

    # 创建一个 n*m 的矩阵，随机填充 '.' 或 '#'
    grid = [[('.', '#')[random.randint(0, 1000) % 5 == 0] if i != 0 and j != 0 and i != n-1 and j != m-1 else '#'
             for j in range(m)] for i in range(n)]

    # 找到所有的 '.' 位置
    empty_positions = [(i, j) for i in range(n)
                       for j in range(m) if grid[i][j] == '.']

    # 随机选择两个不同的 '.' 位置设置为 'S' 和 'T'
    if len(empty_positions) >= 2:
        start, end = random.sample(empty_positions, 2)
        grid[start[0]][start[1]] = 'S'
        grid[end[0]][end[1]] = 'T'
    else:
        print("没有足够的 '.' 来放置 'S' 和 'T'")
        assert 0

    return grid, n, m


def print_grid(grid):
    for row in grid:
        print(''.join(row))


grid, n, m = generate_random_matrix(10)
print(n, m)
print_grid(grid)
