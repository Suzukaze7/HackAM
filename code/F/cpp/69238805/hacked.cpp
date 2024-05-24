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
int a[105];
int main()
{
    int n;
    cin>>n;
    int i;
    for(i=1;i<=n;i++) cin>>a[i];
    int cnt=0;
    for(i=1;i<=n;i++)
    {
        if(a[i]&1) cnt++;
    }
    if(cnt&1)
    {
        cout<<-1;
        return 0;
    }
    cnt=cnt/2;
    for(i=1;i<=n;i++)
    {
        if(a[i]%2==0) cnt++;
    }
    cout<<cnt;
    return 0;
}