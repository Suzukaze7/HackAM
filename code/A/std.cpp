#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
#include<string>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<vector>
#include<set>
#include<unordered_set>
#include<bitset>
#include<climits>
#include<numeric>
#include<functional>
#include<iomanip>
#ifdef YJL
#include<debug.h>
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;
const vector<int> dx{0,1,0,-1};
const vector<int> dy{1,0,-1,0};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    auto toId = [&](int i,int j) {
        return i*m+j;
    };

    vector<vector<char>> a(n,vector<char>(m));
    vector<vector<int>> nxt(n*m,vector<int>(4, -1));
    int s = -1, t = -1;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin>>a[i][j];
            if(a[i][j]=='#') continue;
            int u = toId(i, j);

            if(a[i][j]=='S') s = u;
            if(a[i][j]=='T') t = u;
            for(int k=0; k<4; ++k) {
                nxt[u][k] = u;
            }
            if(i and a[i-1][j]!='#') {
                nxt[u][3] = nxt[toId(i-1, j)][3];
            }
            if(j and a[i][j-1]!='#') {
                nxt[u][2] = nxt[toId(i, j-1)][2];
            }
        }
    }
    for(int i=n-1; i>=0; --i) {
        for(int j=m-1; j>=0; --j) {
            if(a[i][j]=='#') continue;
            int u = toId(i, j);
            if(i+1 < n and a[i+1][j]!='#') {
                nxt[u][1] = nxt[toId(i+1, j)][1];
            }
            if(j+1 < m and a[i][j+1]!='#') {
                nxt[u][0] = nxt[toId(i, j+1)][0];
            }
        }
    }

    vector<int> d(n*m, 1e9);
    d[s] = 0;
    vector<int> q;
    q.push_back(s);
    for(int k=0; k<q.size(); ++k) {
        int u = q[k];
        if(u == t) {
            cout<<d[u]<<'\n';
            exit(0);
        }

        for(int j=0; j<4; ++j) {
            int v = nxt[u][j];
            if(d[v] > d[u]+1) {
                d[v] = d[u]+1;
                q.push_back(v);
            }
        }
    }
    cout<<"-1\n";
    return 0;
}
/*




*/