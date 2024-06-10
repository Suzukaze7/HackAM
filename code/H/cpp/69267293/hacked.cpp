#include<iostream>
#include <cassert>
#include<unordered_map>

using namespace std;

const int N = 1e5 + 100;

long long f[N];

long long dfs(int x)
{
	if(f[x])	return f[x];

	long long res = 1;

	for(int i = 1;i <= x / i;i++)
		if(x % i == 0)
		{
			res += dfs(i);
			if(x / i != i && x / i != x)
				res += dfs(x / i);
		}

	return f[x] = res;
}

int main()
{
	int T, x;
	cin >> T;

	assert(1 <= T && T <= 1e5);

	f[1] = 1;
	for(int i = 1e5; i > 1; i --)
		dfs(i);

	while(T--)
	{
		scanf("%d", &x);
		assert(1 <= x && x <= 1e5);

		printf("%lld ", dfs(x));

	}

	return 0;
}