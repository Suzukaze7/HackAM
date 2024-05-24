#include <bits/stdc++.h>

#define int long long
using namespace std;


void solve() {
    int n,m;cin>>n>>m;
    vector<string> a(n+1);
    set<int> ans,doc;
    for(int i=1;i<=n;i++) cin>>a[i],doc.insert(i);
    doc.insert(1e9);
    bool ok=false;
    for(int i=1,j=1;i<=m;i++){
        string s;cin>>s;
        if(a[j]==s){
            if(!ok) ans.insert(j),doc.erase(j);
            ok=false;
            j=*doc.lower_bound(j+1);
            if(j==1e9) j=*doc.begin();
            if(j==1e9) break;
        }else{
            ok=true;
        }
    }
    for(auto x:ans) cout<<a[x]<<"\n";
}

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}