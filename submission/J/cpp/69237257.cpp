#include <bits/stdc++.h>
 #define int long long
using namespace std;
  void solve() {
    int n;cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        sum+=x;
    }
    cout<<max(0ll,sum-50)<<"\n";
}
 signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}