#include <bits/stdc++.h>

#define int long long
using namespace std;


void solve() {
    int n;cin>>n;
    vector<int> a(n+1);
    int cnt=0;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(a[i]&1) cnt++;
    }
    if(cnt&1) cout<<-1<<"\n";
    else{
        cout<<n-cnt+cnt/2<<"\n";
    }
    

}

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}