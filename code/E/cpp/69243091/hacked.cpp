#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
string s[N];
int n,m;
int st[N];
int main(){
    cin >> n >> m;
    queue<pair<string,int>> q;
    for(int i = 0; i < n; i ++){
        cin >> s[i];
        q.push({s[i],i});
    }
    map<string,int> mp;
    int idx = 0;
    int f = 1;
    for(int i = 0; i < m; i ++){
        string t;
        cin >> t;
        if(q.empty()) continue;
        auto ss = q.front();
        string tt = ss.first;
//         cout << t << endl;
//         cout << tt << endl;
        if(t == tt){
            if(f){
                st[ss.second] = 1;
                q.pop();
            }
            else{
                q.pop();
                q.push(ss);
                f = 1;
            }
        }else{
            f = 0;
        }
    }
    for(int i = 0; i < n; i ++){
        if(st[i]) cout << s[i] << endl;
    }
    return 0;
}