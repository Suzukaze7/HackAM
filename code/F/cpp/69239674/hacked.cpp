#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long  
#define pb push_back
#define fi first
#define se second
using namespace std;
const int INF=1e6+5;
int n,a[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;int sum=0;
    for (int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
    if (sum&1) {cout<<"-1\n";return 0;}
    for (int i=1;i<=n;i++) a[i]%=2;
    sum=0;
    int ans=0;
    for (int i=1;i<=n;i++)
        if (a[i]&1) sum++;
        else ans++;
    cout<<ans+sum/2<<"\n";
    return 0;
}