#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<climits>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<bitset>
#include<cmath>
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#include "debug.h"
#endif

#define x first 
#define y second 
#define ALL(a) a.begin(),a.end()
using namespace std;

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
typedef long long LL;
const int N = 2e5 + 10,M = N * 35,INF = 0x3f3f3f3f;
struct Node  
{
    int l,r;
    int lval,rval;
    int min,posOfMin;
    int localMin = INF,plm;
}tr[N << 2];
int a[N];
int n,q;

struct SegmentTree
{
    /* data */
    void build(int u,int l,int r)
    {
        if(l == r) tr[u] = {l,r,a[l],a[l],a[l],l};
        else 
        {
            int mid = l + r >> 1;
            tr[u] = {l,r};
            build(u << 1,l,mid);
            build(u << 1 | 1,mid + 1,r);
            pushUp(u);
        }
    }

    void pushUp(int u)
    {
        pushUp(tr[u],tr[u << 1],tr[u << 1 | 1]);
    }

    void pushUp(Node &root,Node &left, Node &right)
    {
        int lr = left.r, rl = right.l;
        int newlow = INF, newloc = 0;
        if(a[left.l] <= a[left.l + 1]) newlow = a[left.l], newloc = left.l;
        if(lr - 1 >= left.l && a[lr] <= a[lr - 1] && a[rl] >= a[lr] && newlow > a[lr]) newlow = a[lr], newloc = lr;
        if(rl + 1 <= right.r && a[lr] >= a[rl] && a[rl] <= a[rl + 1] && newlow > a[rl]) newlow = a[rl], newloc = rl;
     //   debug(left.l,right.r,newlow,left.localMin,right.localMin);
        if(left.localMin <= newlow) 
        {
            newlow = left.localMin;
            newloc = left.plm;
        }
        if(right.localMin < newlow)
        {
            newlow = right.localMin;
            newloc = right.plm;
        }
        int newMin,minPos;
        if(left.min >= right.min) minPos = right.posOfMin, newMin = right.min;
        else minPos = left.posOfMin, newMin = left.min;
        root = {left.l,right.r,left.lval,right.rval,newMin,minPos,newlow,newloc};  
    }

    Node query(int u,int l,int r)
    {
        if(tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        Node res,left,right;
        int flag = 0;
        if(l <= mid) 
        {
            flag += 1;
            left = query(u << 1,l,r);
        }
        if(r > mid) 
        {
            flag += 2;
            right = query(u << 1 | 1,l,r);
        }
        if(flag == 1) return left;
        else if(flag == 2) return right;
        pushUp(res,left,right);
        return res;
    }
}seg;

struct SegmentTreePlus
{
    int lch[(N << 2) + M], rch[(N << 2) + M], root[N], idx = 0;
    LL sum[(N << 2) + M];

    void cpy(int from,int to)
    {
        lch[to] = lch[from];
        rch[to] = rch[from];
        sum[to] = sum[from];
    }

    int modify(int pre,int l,int r,int pos,int x)
    {
        int now = ++idx;
        cpy(pre,now);
        sum[now] ++;
        if(l == r) return now;
        int mid = l + r >> 1;
        if(pos <= mid) lch[now] = modify(lch[pre],l,mid,pos,x);
        else rch[now] = modify(rch[pre],mid + 1,r,pos,x);
        return now;
    }

    LL query(int start,int ed,int l,int r,int ql,int qr)
    {
        if(l == ql && r == qr) return sum[ed] - sum[start];
        int mid = l + r >> 1;
        if(qr <= mid) return query(lch[start],lch[ed],l,mid,ql,qr);
        if(ql > mid) return query(rch[start],rch[ed],mid + 1,r,ql,qr);
        return query(lch[start],lch[ed],l,mid,ql,mid) + 
                query(rch[start],rch[ed],mid + 1,r,mid + 1,qr);
    }
}segg;


int main()
{

    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        segg.root[i] = segg.modify(segg.root[i - 1],0,1e9,a[i],a[i]);
    }
    seg.build(1,1,n);
    // debug(tr,36);
  //  for(int i = 1; i <= 60; i++) debug(tr[i].localMin,tr[i].plm);
    while(q--)
    {
        int l,r;
        cin >> l >> r;
        Node res = seg.query(1,l,r);
        //debug(res.min,res.posOfMin);
        if(res.posOfMin != res.r) 
        {
            int cnt = segg.query(segg.root[res.l - 1],segg.root[r],0,1e9,0,res.min);
            //debug(cnt);
            cout << r - l + 1 - cnt << "\n";
        }
        else 
        {
            if(res.plm)
            {
                int cnt = segg.query(segg.root[res.plm - 1],segg.root[r],0,1e9,0,res.localMin);
               // debug(res.plm,cnt);
                if(cnt == res.r - res.plm + 1) cnt = segg.query(segg.root[l - 1],segg.root[r],0,1e9,0,res.lval);
                else cnt = segg.query(segg.root[l - 1],segg.root[r],0,1e9,0,res.localMin);
                cout << r - l + 1 - cnt << "\n";
            }
            else 
            {
                int cnt = segg.query(segg.root[l - 1],segg.root[r],0,1e9,0,res.lval);
           //     debug(res.plm,cnt);
                cout << r - l + 1 - cnt << "\n";
            }
        }
    }
    return 0;
}
