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
int const N=2e5+7,M=2e6+7;
int const INF=0x3f3f3f3f;
LL const INFF=0x3f3f3f3f3f3f3f3f;

int n,m,q,k;
int x,y,z;
int a[N];
string s[N],t[N];
bool vis[N];
int p[N];
set<int>se;

int find(int x){
	return p[x]==x?p[x]:find(p[x]);
}

int get(int x){
	return *se.lower_bound(x);
}

void solve(){
    cin>>n>>m;
	se.insert(n);
    for(int i=0;i<n;i++)	cin>>s[i],se.insert(i);
    for(int j=0;j<m;j++)	cin>>t[j];
    
    int cnt=0;
	for(int i=0,j=0;j<m&&cnt<n;j++){
		i=get(i);
		if(i==n)	i=*se.lower_bound(0);
		
		if(t[j]==s[i])	se.erase(i),cnt++;	//第一次匹配成功
		else{
			while(j<m&&t[j]!=s[i]){	//找到一个可以匹配s[i]的t[j]
				j++;
			}
			if(j==m)	break;
		}
		i=get(i+1);	//必须匹配成功，不然直接退出循环了
		if(i==n)	i=get(0);
	}
	for(int i=0;i<n;i++) 
		if(!se.count(i)) cout<<s[i]<<"\n";
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