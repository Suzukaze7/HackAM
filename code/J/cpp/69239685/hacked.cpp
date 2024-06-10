#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long  
#define pb push_back
#define fi first
#define se second
using namespace std;
const int INF=1e6+5;
int n,a[INF],f[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;int sum=0;
    for (int i=1;i<=n;i++) {
        int x=0;cin>>x;
        sum+=x;
    }
    cout<<max(0ll,sum-50)<<"\n";
    return 0;
}