#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=2*N,mod=1e9+7;
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
    cin>>n;
    int a=0,b=0;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        if(x%2==0) a++;
        else b++;
    }
    if(b&1) cout<<"-1\n";
    else
    cout<<a+b/2<<"\n";
}
 signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}