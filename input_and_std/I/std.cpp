#include<bits/stdc++.h>

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

long long n,m,V;
bool st[N];
long long num[N],dp[N];

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m>>V;
    for(int i=1;i<=n;i++)
    {
        cin>>num[i];
    }
    for(int i=1;i<=V;i++)
    {
        dp[i]=-INF;
    }
    long long ans=-1;
    sort(num+1,num+n+1);
    for(int i=1;i<=n;i++)
    {
        if(V>=num[i])ans=max(ans,dp[V-num[i]]+1+num[i]*m);
        for(int j=V;j>=num[i];j--)
        {
            dp[j]=max(dp[j-num[i]]+1,dp[j]);
        }
    }
    cout<<ans;
    return 0;
}
