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
	cin>>n>>k;
	for(int i = 1; i <= n; i++)  cin>>a[i];
    bool f1 = 0, f2 = 0, f3 = 0;
    
    if(n == 1 && a[1] == 1) 
    {
        cout<<"Yes"<<"\n";
        return;
    }
    
    for(int i = 1; i <= n; i++)
    {
        if(i == 1)
        {
            if(a[1] == n) f2 = 1;
            else if(a[1] == 2) f3 = 1;
        }
        else if(i == n) 
        {
            if(a[n] == n - 1) f2 = 1;
            else if(a[n] == 1) f3 = 1;
        }
        else {
            if(a[i] == i + 1) f2 = 1;
            else if(a[i] == i - 1) f3 = 1;
        }
        if(a[i] == i) f1 = 1;
    }
    
    if(k == 1) 
    {
        if(f1) cout<<"Yes"<<"\n";
        else cout<<"No"<<"\n";
        return ;
    }
    
    if(f1 && (f2 || f3)) cout<<"Yes"<<"\n";
    else cout<<"No"<<"\n";
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