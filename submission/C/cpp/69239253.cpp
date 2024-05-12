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
int a[200005];
map<int,int> l,r;
int main()
{
    int n,k;
    cin>>n>>k;
    int i;
    for(i=1;i<=n;i++) cin>>a[i];
    int cnt=0;
    for(i=1;i<=n;i++)
    {
        if(a[i]==i) cnt++;
    }
    if(!cnt)
    {
        cout<<"No";
        return 0;
    }
    if(k==1)
    {
        cout<<"Yes";
        return 0;
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]==i+1||a[i]==i-1)
        {
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    if(a[1]==n||a[n]==1)
    {
        cout<<"Yes"<<endl;
        return 0;
    }
    cout<<"No";
    return 0;
}