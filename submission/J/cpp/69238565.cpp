#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
#define lowbit(x) ((x)&(-(x)))
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define maxheap(x) priority_queue<x,vector<x>,less<x> > 
#define minheap(x) priority_queue<x,vector<x>,greater<x> > 
#define endl '\n'
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef long long ll;
typedef unsigned long long ull;
//#define mod 1000000009
//#define mod 1000000007
int a[15];
int main()
{
    int n;
    int i;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    int sum=0;
    for(i=1;i<=n;i++) sum+=a[i];
    int res=sum<=50?0:sum-50;
    cout<<res;
    return 0;
}