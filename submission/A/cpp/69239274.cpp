#include <bits/stdc++.h>
#define all(arr) arr.begin(), arr.end()
 using namespace std;
 typedef long long LL;
typedef pair<LL, LL> PL;
 const LL N = 1e3 + 5;
const LL mod = 1e9 + 7;
 LL dx[10] = {1, -1, 0, 0, 1, 1, -1, -1};
LL dy[10] = {0, 0, 1, -1, 1, -1, 1, -1};
 struct Node{
    LL x, y, u;
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
 LL n, k, l, r, c, x, y, m, ans, p, sum, t;
LL a[N];
string s;
char ma[N][N];
bool bol = false;
bool vis[N][N][4];
 void bfs(int x, int y, int u){
    queue<Node> q;
    q.push({x, y, u});
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        int x = v.x;
        int y = v.y;
        int u = v.u;
        if(ma[x][y] == 'T'){
            cout << u << endl;
            bol = true;
            return;
        }
        int nx, ny;
        for (int i = 0; i < 4; i ++){
            nx = x + dx[i];
            ny = y + dy[i];
            if(vis[x][y][i]) continue;
            if(dx[i] != 0){
                for (int j = 0; j <= 1000; j ++){
                    vis[(x + dx[i]*(j))][y][i] = true;
                    if(ma[(x + dx[i]*(j + 1))][y] == '#'){
                        q.push({(x + dx[i]*(j)), y, u + 1});
                        break;
                    }
                }
            }
            else{
                for (int j = 0; j <= 1000; j ++){
                    vis[x][y + dy[i]*(j)][i] = true;
                    if(ma[x][y + dy[i]*(j + 1)] == '#'){
                        q.push({x, y + dy[i]*(j), u + 1});
                        break;
                    }
                }
            }
                     }
    }
}
 void solve(){
    ans = 0;
    sum = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++){
        cin >> ma[i] + 1;
    }
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= m; j ++){
            if(ma[i][j] == 'S'){
                bfs(i, j, 0);
            }
        }
    }
    if(!bol){
        cout << -1 << endl;
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