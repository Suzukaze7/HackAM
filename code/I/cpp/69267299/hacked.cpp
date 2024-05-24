#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

const int N = 5100;

int v[N], f[N][N];

int main()
{
	int n, m, V;
	cin >> n >> m >> V;

	assert(1 <= n && n <= 5e3);
	assert(1 <= m && m <= 5e3);
	assert(1 <= V && V <= 5e3);

	for(int i = 1; i <= n; i ++)
	{
		cin >> v[i];
		assert(1 <= v[i] && v[i] <= 5e3);
	}

	sort(v + 1, v + 1 + n);

	memset(f, -1, sizeof(f));
	f[0][0] = 0;			//前 i 个物品凑出价值为 j 的最大数量
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= V; j ++)
		{
			f[i][j] = f[i - 1][j];

			if(j - v[i] >= 0 && f[i - 1][j - v[i]] != -1)
				f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + 1);
		}

	int ans = -1;
	for(int i = 1; i <= n; i ++)
		if(f[i - 1][V - v[i]] != -1)
			ans = max(ans, m * v[i] + 1 + f[i - 1][V - v[i]]);

	cout << ans;




}