#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,k,a[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for (int i=0;i<n;i++) cin>>a[i],a[i]--;
    int fl=0,fl2=0;
    for (int i=0;i<n;i++) {
        if (a[i]==i) fl=1;
        if (a[(i+n-1)%n]==i) fl2=1;
        if (a[(i+1)%n]==i) fl2=1;
    }
    if (!fl) cout<<"No\n";
    else {
        if (k==1) cout<<"Yes\n";
        else if (fl2) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}