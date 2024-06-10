#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,k,a[INF],vis[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for (int i=0;i<n;i++) cin>>a[i],a[i]--;
    for (int i=0;i<n;i++) {
        vis[((a[i]-i)%n+n)%n]=1;
        vis[((a[i]-i)%n+n)%n+n]=1;
    }
    int kk=0;
    while (vis[kk]) kk++;
    if (kk>=k) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}