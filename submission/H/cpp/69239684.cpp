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
    for (int i=1;i<=1e5;i++) {
        f[i]++;
        for (int j=1;j*j<=i;j++) {
            if (i%j) continue;
            if (i!=j) f[i]+=f[j];
            if (i/j!=j && i/j!=i) f[i]+=f[i/j];
        }
    }
    cin>>n;
    for (int i=1;i<=n;i++) {
        int x=0;cin>>x;
        cout<<f[x]<<" ";
    }
    cout<<"\n";
    return 0;
}