#include <bits/stdc++.h>
 #define int long long
using namespace std;
  void solve() {
    int n,k;cin>>n>>k;
    vector<int> a(n+1);
    set<int> se;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(a[i]>=i) se.insert(a[i]-i);
        else se.insert(n-i+a[i]);
    }
    int mex=0;
    while(se.count(mex)) mex++;
    if(mex>=k) cout<<"Yes\n";
    else cout<<"No\n";
 }
 signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}