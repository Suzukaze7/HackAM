#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=2*N,mod=1e9+7;
#define int long long
#define uLL unsigned long long
const int inf=1e18;
typedef pair<int,int> PII;
typedef long long LL;
using node=tuple<int,int,int>;
int n,m,k;
int a[N];
string s[N];
void solve()
{
    cin>>n>>m;
    unordered_map<string,int> mp;
    queue<int> q;
    for(int i=0;i<n;i++){
        cin>>s[i];
        mp[s[i]]++;
        q.push(i);
    }
    int idx=0;
    int now=0;
    vector<int> res;
    
    while(m--)
    {
        if(q.empty()) continue;
        idx=q.front();
        string t;cin>>t;
        
        if(t==s[idx])
        {
            q.pop();
            if(now==0)
            {
                res.push_back(idx);
            }else q.push(idx);
            now=0;
        }else now++;
    }
    sort(res.begin(),res.end());
    for(auto x:res) cout<<s[x]<<"\n";
}

signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}