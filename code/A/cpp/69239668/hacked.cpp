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
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin>>a[i][j];
    for (int i=1;i<=n;i++) {
        int L=0;
        for (int j=1;j<=m;j++) {
            if (a[i][j]=='#') L=0;
            else if (!L) L=j;
            if (ys(i,j)!=ys(i,L)) add_edge(ys(i,j),ys(i,L));
        }
        L=0;
        for (int j=m;j;j--) {
            if (a[i][j]=='#') L=0;
            else if (!L) L=j;
            if (ys(i,j)!=ys(i,L)) add_edge(ys(i,j),ys(i,L));
        }
    }
    for (int j=1;j<=m;j++) {
        int L=0;
        for (int i=1;i<=n;i++) {
            if (a[i][j]=='#') L=0;
            else if (!L) L=i;
            if (ys(i,j)!=ys(L,j)) add_edge(ys(i,j),ys(L,j));
        }
        L=0;
        for (int i=n;i;i--) {
            if (a[i][j]=='#') L=0;
            else if (!L) L=i;
            if (ys(i,j)!=ys(L,j)) add_edge(ys(i,j),ys(L,j));
        }
    }
    // cerr<<n<<" "<<m<<" iawojero\n";
    int s=0,t=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) {
            if (a[i][j]=='S') s=ys(i,j);
            if (a[i][j]=='T') t=ys(i,j);
        }
    memset(dis_,63,sizeof dis_);
    dis_[s]=0;q.push(s);
    while (q.size()) {
        int x=q.front();q.pop();
        for (int i=head[x];i;i=edge[i].next_) {
            int v=edge[i].to_;
            if (dis_[v]>dis_[x]+1) {
                dis_[v]=dis_[x]+1;
                q.push(v);
            }
        }
    }
    if (dis_[t]>1e17) cout<<"-1\n";
    else cout<<dis_[t]<<"\n";
    return 0;
}