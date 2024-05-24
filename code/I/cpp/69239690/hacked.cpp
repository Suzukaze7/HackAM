#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long  
#define pb push_back
#define fi first
#define se second
using namespace std;
const int INF=5e3+5;
int n,f[3][INF],m,x,p[INF];
signed main()
{
    memset(f,-63,sizeof f);
    ios::sync_with_stdio(false);
    cin>>n>>m>>x;
    for (int i=1;i<=n;i++) cin>>p[i];
    sort(p+1,p+1+n,greater<int>());
    f[0][0]=0;
    for (int i=1;i<=n;i++) {
        int u=i&1,v=u^1;
        memset(f[u],-63,sizeof f[u]);
        for (int j=0;j<=x;j++) f[u][j]=f[v][j];
        for (int j=x;j>=p[i];j--) 
            f[u][j]=max(f[u][j],f[v][j-p[i]]+1+(j-p[i]==0?m*p[i]:0));
    }
    if (f[n&1][x]<-1e17) cout<<"-1\n";
    else cout<<f[n&1][x]<<"\n";
    return 0;
}