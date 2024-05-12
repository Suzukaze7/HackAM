#include<bits/stdc++.h>
using namespace std;
const int N=5010+10,M=2*N,mod=1e9+7;
#define int long long
#define uLL unsigned long long
const int inf=1e18;
typedef pair<int,int> PII;
typedef long long LL;
using node=tuple<int,int,int>;
int n,m,k;
int a[N];
void solve()
{
    int v;
    cin>>n>>m>>v;
    vector<int> f(v+10,-inf);
         for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    int res=-1;
    f[0]=0;
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
        if(v>=a[i])
        {
            res=max(res,f[v-a[i]]+1+m*a[i]);    
        }
        for(int j=v;j>=0;j--)
        {
            if(j-a[i]>=0) f[j]=max(f[j],f[j-a[i]]+1);
        }
      //  if(f[v]>=1) res=max(res,f[v]+a[i]*m);
    }
    cout<<res;
}
 signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}