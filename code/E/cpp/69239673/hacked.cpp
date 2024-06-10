#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long  
#define pb push_back
#define fi first
#define se second
using namespace std;
const int INF=1e6+5;
int n,m;
string s1[INF];
queue < pair<ull,int> >q;
vector <int> ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for (int i=1;i<=n;i++) {
        cin>>s1[i];
        ull h1=0;
        for (char c:s1[i]) h1=h1*233+c;
        q.push({h1,i});
    }
    while (q.size() && m>0) {
        pair<ull,int> it=q.front();q.pop();
        int fl=0,fl2=0;
        while (m--) {
            string t;cin>>t;
            // cerr<<t<<" "<<it.se<<" awoiejrwaqw\n";
            ull h1=0;
            for (char c:t) h1=h1*233+c;
            if (h1==it.fi && !fl) {ans.pb(it.se),fl2=1;break;}
            if (h1==it.fi) break;
            fl=1;
        }
        if (!fl2) q.push(it);
    }
    sort(ans.begin(),ans.end());
    for (int i:ans) cout<<s1[i]<<"\n";
    return 0;
}