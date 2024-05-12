#include <bits/stdc++.h>
#define all(arr) arr.begin(), arr.end()
 using namespace std;
 typedef long long LL;
typedef pair<LL, LL> PL;
 const LL N = 3e5 + 5;
const LL mod = 1e9 + 7;
 LL dx[10] = {1, -1, 0, 0, 1, 1, -1, -1};
LL dy[10] = {0, 0, 1, -1, 1, -1, 1, -1};
 struct Node{
    LL st, ed;
    bool operator < (const Node &a) const{
        if(st == a.st) return ed < a.ed;
        else return st < a.st;
    }
};
LL lowbit(LL x){
    return (x)&(-x);
}
LL ksm(LL a,LL b)         //快速幂求逆元时间复杂度为O(logn)
{
    LL ans = 1, base = a;
    while(b)
    {
        if(b&1)
            ans = (base*ans)%mod;
        base = (base*base)%mod;
        b >>= 1;
    }
    return ans;
}
 LL inv(LL x, LL p){
    return ksm(x, p - 2);
}
   LL n, k, l, r, c, x, y, m, ans, p, q, sum;
LL a[N];
LL len[N];
string s;
struct tree
{
    struct node
    {
        int l,r,sum,mx;
        node(){
            mx = -2e9;
        }
    }t[N*4];
    void pushup(int k)
    {   
        t[k].mx = max(t[k*2].mx,t[k*2+1].mx);
        if(t[k*2].mx == t[k*2+1].mx) t[k].sum = t[k*2].sum + t[k*2+1].sum;
        else t[k].sum = (t[k*2].mx>t[k*2+1].mx?t[k*2].sum:t[k*2+1].sum);
    }
    void build(int l,int r,int k = 1)
    {
        t[k].l = l;t[k].r = r;
        if(l == r)
        {
            t[k].mx = -a[l];
            t[k].sum = 1;
            return;
        }
        int mid = (l+r)/2;
        build(l,mid,k*2);
        build(mid+1,r,k*2+1);
        pushup(k);
    }
    void update(int x,int y,int k = 1)
    {
        if(t[k].l == x && t[k].r == x)
        {
            t[k].mx = y;
            return;
        }
        if(x <= t[k*2].r) update(x,y,k*2);
        else update(x,y,k*2+1);
        pushup(k);
    }
    pair<int,int> query(int l,int r,int k = 1)
    {
        if(l <= t[k].l && t[k].r <= r)
        {
            return {t[k].mx,t[k].sum};
        }
        pair<int,int> p = {-2e9,0};
        if(l <= t[k*2].r)
        {
            pair<int,int> p1 = query(l,r,k*2);
            if(p.first == p1.first) p.second += p1.second;
            else if(p.first < p1.first)  p = p1;
        }
        if(r >= t[k*2+1].l)
        {
            pair<int,int> p1 = query(l,r,k*2+1);
            if(p.first == p1.first) p.second += p1.second;
            else if(p.first < p1.first)  p = p1;
        }
        return p;
    }
}st;
 void solve(){
    ans = 0;
    sum = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    st.build(1, n);
         for (int i = n; i >= 1; i --){
        int j = i;
        while(a[j - 1] >= a[j] && j - 1 >= 1){
            j --;
        }
        for (int k = i; k >= j; k --){
            len[k] = j;
        }
        i = j;
    }
         while(q --){
        cin >> l >> r;
        p = len[r];
        if(p <= l){
            cout << 0 << endl;
            continue;
        }
        else{
            LL t;
            PL pl = st.query(l, p - 1);
            LL minn = -pl.first;
            LL sum = pl.second;
            //cout << "p = " << p << " minn = " << minn << " sum = " << sum  << endl;
            LL ll = p, rr = r;
            LL mid = (ll + rr) >> 1;
            while(ll < rr){
                mid = (ll + rr) >> 1;
                //                 cout << "mid = " << mid << endl;
                if(minn >= a[mid]){
                    rr = mid;
                }
                else ll = mid + 1;
            }
            //cout << "ll = " << ll << "  ";
            if(minn >= a[ll]){
                cout << ll - l - 1 - (sum - 1) << endl;
            }
            else cout << ll - l - (sum - 1) << endl;
        }
    }
}
 int main(){
    int T = 1;
    //cin >> T;
    while(T --){
        solve();
    }
}
//LL fac[N], nfac[N], invv[N], mul[N];// fac是全排列，乘以逆元(nfax)等于除以(fac)
//inline LL C(LL a, LL b){
//  return a < b ? 0:1LL*fac[a]*nfac[b]%mod*nfac[a - b]%mod;
//}
//
//void init(){
//  mul[0] = 1;
//  for(int i = 1; i < N; i ++)
//      mul[i]=(mul[i-1]+mul[i-1])%mod;
//  fac[0] = fac[1] = invv[1] = nfac[0] = nfac[1] = 1;
//  for(int i = 2; i < N; i ++){
//      fac[i] = 1LL*fac[i - 1]*i%mod,
//      invv[i] = mod - 1LL*(mod/i)*invv[mod%i]%mod,
//      nfac[i] = 1LL*nfac[i - 1]*invv[i]%mod;
//  }
//}
//
//void add(int f[],int x,int y){for(;x<=n;x+=(-x&x)){f[x]+=y;}}
//int get(int f[],int x,int y=0){for(;x;x-=(-x&x)){y+=f[x];}return y;}