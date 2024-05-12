#include<bits/stdc++.h>
 using namespace std;
using ull = unsigned long long;
using ll = long long;
using PII = pair<ll,ll>;
using PIII = pair<ll, pair<ll,ll>>;
#define endl "\n"
#define pb push_back
#define IOS ios::sync_with_stdio(false);cin.tie(0)
#define lowbit(x) (x) & (-x)
#define point(x) setiosflags(ios::fixed)<<setprecision(x)
const int N=1e5+10;
const int INF=0x3f3f3f3f;
const int mod=1e9+7;
 void solve(){
    int n; cin >> n;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n; i ++) {
        int x; cin >> x;
        sum += x;
    }
    //cout << sum << endl;
//     if(sum >= 50) cout << sum - 50;
//     else cout << 0 << endl;
    cout << max(sum - 50, 0) <<  endl;
}
int main()
{
    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}