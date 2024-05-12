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
int const N=1e5+7,M=2e6+7;
int const INF=0x3f3f3f3f;
LL const INFF=0x3f3f3f3f3f3f3f3f;
 int n,m,q,k;
LL f[N];
 void solve(){
    scanf("%d",&n);
    printf("%lld ",f[n]);
} 
  void init(){
    f[1]=1;
    for(int i=2;i<N;i++){
        for(int j=1;j<=i/j;j++){
            if(i%j==0){
                f[i]+=f[j];
                if(i/j!=j)  f[i]+=f[i/j];
            }
        }
    }
}
 int main()
{
    //std::ios::sync_with_stdio(false);   cin.tie(0); cout.tie(0);
    init();
    int T=1;
    //cin>>T;
    scanf("%d",&T);
         for(int i=1;i<=T;i++){
        solve();
    }
         return 0;
}