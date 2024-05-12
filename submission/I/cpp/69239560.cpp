//#pragma GCC optimize(2)
 #include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include<stack>
#include<cmath>
#include <unordered_set>
#include <unordered_map>
#include<set>
#include <map>
#include<ctime>
#include<bitset>
 using namespace std;
 typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int>PII;
 #define fi first
#define se second
#define ls u<<1
#define rs u<<1|1
#define all(ss) ss.begin(),ss.end()
#define pb push_back
  int const mod=1e9+7; 
int const B=507;
//int const mod=998244353; 
//int const base=131,mod=2e9+11;
int const N=5007,M=2e6+7;
int const INF=0x3f3f3f3f;
LL const INFF=0x3f3f3f3f3f3f3f3f;
 int n,m,q,k;
int V;
int v[N];
bool f[N];
 /*
5 4 7
1 1 1 3 3
 */
 void solve(){
    scanf("%d%d%d",&n,&m,&V);
    for(int i=1;i<=n;i++)    scanf("%d",v+i);
    sort(v+1,v+1+n);
    vector<LL>f0(V+1,-INFF);
    vector<LL>f(V+1,-INFF);
         f0[0]=f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=V;j>=v[i];j--){
            f[j]=max(f[j],f0[j-v[i]]+1+1LL*v[i]*m);
        }
        for(int j=V;j>=v[i];j--){
            f0[j]=max(f0[j],f0[j-v[i]]+1);
        }
    }
    cout<<(f[V]<0?-1:f[V]);
          } 
  void init(){
     }
 int main()
{
    //std::ios::sync_with_stdio(false);   cin.tie(0); cout.tie(0);
    //init();
    int T=1;
    //cin>>T;
    //scanf("%d",&T);
         for(int i=1;i<=T;i++){
        solve();
    }
         return 0;
}