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
int main()
{
    int n,k;
    cin>>n>>k;
    int i;
    for(i=1;i<=n;i++) cin>>a[i];
    multiset<int> s;
    for(i=1;i<=n;i++)
    {
        if(a[i]>=i) s.insert(a[i]-i);
        else s.insert(n-i+a[i]);
    }
//    for(auto i:s) cout<<i<<' ';
    for(i=0;i<k;i++)
    {
        if(!s.count(i))
        {
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes";
    return 0;
}