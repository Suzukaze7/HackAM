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
int f[N];
void solve()
{
    f[1]=1;
    for(int i=2;i<=100000;i++){
        int res=0;
        for(int j=1;j<=i/j;j++){
            if(i%j==0){
                if(j!=i)
                res+=f[j];
                if(j*j!=i&&i!=j/i){
                    res+=f[i/j];
                }
            }
        }
        f[i]=res+1;
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        cout<<f[x]<<" ";
    }
}

signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}