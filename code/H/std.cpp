#include<bits/stdc++.h>
#include<fstream>
#include<random>

using namespace std;

#define endl '\n'
#define PII pair<int,int>
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define PLL pair<long long,long long>
#define lowbit(x) (x&(-x))

mt19937_64 rng(random_device{}());
long long myRand(long long l,long long r) {
    uniform_int_distribution<long long> uid(l,r);
    return uid(rng);
}

const int key=5;
const int N=2e6+10;
const long long INF=(1ll<<60);
const long long inf=(1ll<<30);
const int mod=1e9+7;

long long n,num[N],sum[N];

long long dfs(long long n)
{
    if(sum[n]!=0)return sum[n];
    sum[n]=1;
    for(int i=1;i<=n/i;i++)
    {
        if(n%i!=0||i>=n)continue;
        sum[n]+=dfs(i);
        if(n/i!=i&&i!=1)sum[n]+=dfs(n/i);
    }
    return sum[n];
}

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>num[i];
        cout<<dfs(num[i])<<" ";
    }
	return 0;
}
