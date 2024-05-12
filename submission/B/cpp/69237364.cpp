#include<bits/stdc++.h>
 using namespace std;
 #define lowbit(x) (x & (-x)) 
#define ll long long 
#define pb push_back
#define ins insert
#define ls rt << 1
#define rs rt << 1 | 1
typedef pair<int, int> P;
typedef pair<int, P> Q;
const int N = 1e6 + 7;
const int mod = 1e9 + 7;
int n,m,k;
int a[N];
int fac[N], infac[N];
int xx[] = {0,1,0,-1,1,1,-1,-1}, yy[] = {1,0,-1,0,-1,1,-1,1}; 
string s;
ll gcd(ll x,ll y){return y == 0 ? x : gcd(y,x % y);}
ll lcm(ll x,ll y){return x / gcd(x, y) * y;} 
ll qmul(ll a, ll b, ll mod){ll res = 0;while(b){if(b & 1) b -= 1, res = (res + a) % mod;b /= 2;a = (a + a) % mod;}return res;}
ll qmi(ll a, ll b, ll mod){ll res = 1;while(b){if(b & 1) res = res * a % mod;a = a * a % mod;b >>= 1;}return res;}
ll get_C(int n,int m){return fac[n] * infac[m] % mod * infac[n - m] % mod;}
 void solve()
{
    cout<<"50";
}
 int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--) solve();
    return 0;
}