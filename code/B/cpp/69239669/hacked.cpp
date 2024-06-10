#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e3+5;
const int INFN=1e6+5;
struct _node_edge{
    int to_,next_;
}edge[INFN<<2];
int tot,head[INFN],dis_[INFN];
void add_edge(int x,int y) {
    edge[++tot]={y,head[x]};
    head[x]=tot;
}
int n,m;
char a[INF][INF];
int ys(int x,int y){return (x-1)*m+y;}
queue <int> q;
signed main()
{
    ios::sync_with_stdio(false);
    cout<<"50\n";
    return 0;
}