#include <bits/stdc++.h>

#define int long long
using namespace std;


void solve() {
    int n;cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<int> f(1e5+5);
    f[1]=1;

    function<int(int)> dfs=[&](int x){
        if(f[x]) return f[x];
        f[x]=1;
        for(int i=1;i*i<=x;i++){
            if(x%i==0){
                f[x]+=dfs(i);
                if(i*i!=x&&i!=1){
                    f[x]+=dfs(x/i);
                }
            }
        }
        return f[x];
    };
    for(int i=1;i<=n;i++){
        if(f[a[i]]) cout<<f[a[i]]<<" ";
        else{
            cout<<dfs(a[i])<<" ";
        }
    }
}

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}