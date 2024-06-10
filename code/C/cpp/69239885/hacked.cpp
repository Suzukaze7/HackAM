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
const int N=200100;
int a[N],b[2];
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,k,i;
	cin>>n>>k;
	for(i=1;i<=n;++i)
		cin>>a[i];
	a[0]=a[n];
	a[n+1]=a[1];
	for(i=1;i<=n;++i)
	{
		if(a[i]==i)
			++b[0];
		if(a[i-1]==i)
			++b[1];
		if(a[i+1]==i)
			++b[1];
	}
	if(k==1)
	{
		if(b[0]>0)
			cout<<"Yes";
		else
			cout<<"No";
	}
	else
	{
		if(b[0]>0&&b[1]>0)
			cout<<"Yes";
		else
			cout<<"No";
	}
	return 0;
}