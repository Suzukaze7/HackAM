#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <bitset>
using namespace std;
using ll=long long;
const int N=100100;
ll d[N];
vector<int> e[N];
bool b[N];
vector<int> c;
void sx()
{
	int m=(int)sqrt(N+2)+2,i,j;
	b[0]=b[1]=true;
	for(i=2;i<m;++i)
		for(j=i*i;j<N;j+=i)
			b[j]=true;
//	for(i=2;i<N;++i)
//		if(!b[i])
//			c.emplace_back(i);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,i,j,x;
	sx();
	for(i=1;i<N;++i)
		for(j=i*2;j<N;j+=i)
			e[j].emplace_back(i);
	d[1]=1;
	for(i=2;i<N;++i)
	{
		if(!b[i])
			d[i]=2;
		else
		{
			for(int &y:e[i])
				d[i]+=d[y];
			++d[i];
		}
	}
	cin>>n;
	for(i=0;i<n;++i)
	{
		cin>>x;
		cout<<d[x]<<' ';
	}
	return 0;
}