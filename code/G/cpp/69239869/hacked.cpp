#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long  
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=2e5+5;
int n,q,a[INF];
pii mer(pii a,pii b) {
    pii c;
    if (a.fi>b.fi) c=b;
    else if (a.fi<b.fi) c=a;
    else c={a.fi,b.se+a.se};
    return c;
}
struct Segment{
    #define ll tl[id]
    #define rr tr[id]
    #define ls(x) x<<1
    #define rs(x) x<<1|1
    int tl[INF<<2],tr[INF<<2];
    pii sum[INF<<2],sum2[INF<<2];
    void push_up(int id) {
        sum[id]=min(sum[ls(id)],sum[rs(id)]);
        sum2[id]=mer(sum2[ls(id)],sum2[rs(id)]);
    }
    void build(int l,int r,int id) {
        ll=l;rr=r;
        if (ll==rr) {
            sum[id]={a[l],l};
            sum2[id]={a[l],1};
            return ;
        }
        int Mid=(ll+rr)>>1;
        build(ll,Mid,ls(id));
        build(Mid+1,rr,rs(id));
        push_up(id);
    } 
    pii query(int l,int r,int id) {
        if (l<=ll && rr<=r) return sum[id];
        int Mid=(ll+rr)>>1;
        if (l>Mid) return query(l,r,rs(id));
        else if (r<=Mid) return query(l,r,ls(id));
        else return min(query(l,r,ls(id)),query(l,r,rs(id)));
    }
    pii query2(int l,int r,int id) {
        if (l<=ll && rr<=r) return sum2[id];
        int Mid=(ll+rr)>>1;
        if (l>Mid) return query2(l,r,rs(id));
        else if (r<=Mid) return query2(l,r,ls(id));
        else return mer(query2(l,r,ls(id)),query2(l,r,rs(id)));
    }
    #undef ll
    #undef rr
    #undef ls
    #undef rs
}T1;
set <int> s;
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for (int i=1;i<=n;i++) cin>>a[i];
    T1.build(1,n,1);
    for (int i=2;i<=n;i++) 
        if (a[i-1]<a[i]) s.insert(i);
    for (int i=1;i<=q;i++) {
        int l=0,r=0;
        cin>>l>>r;
        auto it=s.upper_bound(r);
        if (it==s.begin()) {cout<<"0\n";continue;}
        it--;
        if ((*it)-1<l) {cout<<"0\n";continue;}
        if (a[r]==a[*it]) {
            cout<<r-l+1-T1.query2(l,r,1).se<<"\n";
            continue;
        }
        int Min1=T1.query(l,*it,1).se;
        int L=(*it)+1,R=r,ans=-1;
        while (L<=R) {
            int Mid=(L+R)>>1;
            if (a[Min1]>=a[Mid]) R=(ans=Mid)-1;
            else L=Mid+1;
        }
        if (ans==-1) {cout<<r-l+1-T1.query2(l,r,1).se<<"\n";continue;}
        cout<<r-l+1-(r-ans+1)-T1.query2(l,*it,1).se<<"\n";
    }
    return 0;
}