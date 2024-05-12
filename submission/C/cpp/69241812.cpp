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
string s[N];
void solve()
{
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++)
    {
        if(a[i]==i+1)
        {
            if(k==1){
                cout<<"Yes\n";return ;
            }
            bool f=false;
            for(int i=0;i<n;i++){
                if(a[(i+1)%n]==i+1){
                    f=true;
                }
            }
            for(int i=0;i<n;i++){
                if(a[(i-1+n)%n]==i+1){
                    f=true;
                }
            }
            if(f==true){
                cout<<"Yes\n";return ;
            }
            break;
        }    
    }
         cout<<"No\n";
}
 signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}