#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

const int N = 1100;

char g[N][N];
int d[N][N][5], dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);

	for(int i = 1; i <= n; i ++)
		scanf("%s", g[i] + 1);

	int sx, sy, ex, ey;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(g[i][j] == 'S')
				sx = i, sy = j;
			else if(g[i][j] == 'T')
				ex = i, ey = j;

	memset(d, 0x3f, sizeof(d));
	d[sx][sy][4] = 0;

	queue<tuple<int, int, int>> Q;
	Q.push({ sx, sy, 4 });

	while(Q.size())
	{
		auto [x, y, t] = Q.front();
		Q.pop();

		// clog << x << " " << y << " " << t << '\n';

		if(t == 4)
		{
			for(int i = 0; i < 4; i ++)
			{
				int xx = x + dx[i], yy = y + dy[i];
				if(1 <= xx && xx <= n && 1 <= yy && yy <= m)
				{
					if(g[xx][yy] == '.' || g[xx][yy] == 'T' || g[xx][yy] == 'S')
					{
						if(d[xx][yy][i] > d[x][y][t])
							d[xx][yy][i] = d[x][y][t], Q.push({ xx, yy, i });
					}
				}
			}
		}
		else
		{
			int xx = x + dx[t], yy = y + dy[t];
			if(1 <= xx && xx <= n && 1 <= yy && yy <= m)
			{
				if(g[xx][yy] == '.' || g[xx][yy] == 'T' || g[xx][yy] == 'S')
				{
					if(d[xx][yy][t] > d[x][y][t])
						d[xx][yy][t] = d[x][y][t], Q.push({ xx, yy, t });
				}
				else if(g[xx][yy] == '#')
				{
					if(d[x][y][4] > d[x][y][t] + 1)
						d[x][y][4] = d[x][y][t] + 1, Q.push({ x, y, 4 });
				}
			}
		}
	}

	// for(int i = 1; i <= n; i ++)
	// {
	// 	for(int j = 1; j <= m; j ++)
	// 		clog << d[i][j][4] << " ";
	// 	clog << '\n';
	// }

	// cout << ex << " " << ey << '\n';

	if(d[ex][ey][4] == 0x3f3f3f3f)
		puts("-1");
	else
		cout << d[ex][ey][4];

	return 0;
}