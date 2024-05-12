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
    for(int i=1;i<=n;i++) cin>>a[i];
    unordered_map<int,int> mp;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==i) mp[0]++;
        else if(a[i]>i) mp[a[i]-i]++;
        else mp[n-abs(a[i]-i)]++;
    }
    if(mp.size()>=n){
        cout<<"Yes\n";return ;
    }
    for(int i=0;i<n;i++){
        if(mp.count(i)){
            if(i+1>=k){
                cout<<"Yes\n";return ;
            }
        }else break;
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