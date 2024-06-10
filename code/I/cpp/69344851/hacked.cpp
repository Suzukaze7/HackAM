#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 2e6 + 10;
int v[N];
int f[N];
bool cmp(int x,int y){
    return x > y;
}
signed main(){
    int n,m,V;
    cin >> n >> m >> V;
    for(int i = 1; i <= n; i ++){
        cin >> v[i];
    }
    sort(v + 1,v + 1 + n);
    int ans = 0;
    for(int i = 1; i <= V; i ++){
        f[i] = -0x3f3f3f3f;
    }
    for(int i = 1; i <= n; i ++){
        if(V >= v[i]) ans = max(ans,f[V - v[i]] + 1 + v[i] * m);
        for(int j = V; j >= v[i]; j --){
            f[j] = max(f[j],f[j - v[i]] + 1);
        }
    }
    if(ans == 0) cout << -1;
    else cout << ans;
    return 0;
}