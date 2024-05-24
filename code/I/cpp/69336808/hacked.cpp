#include<bits/stdc++.h>
using namespace  std;
typedef long long ll;
const int N=5000+10,INF=1e9;
int v[N];
ll dp[N];
void solve()
{
    int n,m,V;
    cin>>n>>m>>V;
    for(int i=1;i<=n;i++)
    {
        cin>>v[i];
    }
    for(int i=1;i<=V;i++)
    {
        dp[i]=-INF;
    }
    sort(v+1,v+1+n);
    ll ans=-1;
    for(int i=1;i<=n;i++)
    {
        if(V>=v[i]) ans=max(ans,dp[V-v[i]]+1+m*v[i]);
        for(int j=V;j>=v[i];j--)
        {
            dp[j]=max(dp[j],dp[j-v[i]]+1);
        }
    }
    cout<<ans<<endl;
}
int main()
{
	int t;	
	t=1;
	while(t--)
	{
	solve();
	}
	return 0;
}
