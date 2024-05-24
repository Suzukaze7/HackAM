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
int a[100005];
ll f[100005];
int main()
{
    int n;
    cin>>n;
    int i;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<=100000;i++)
    {
        if(i==1)
        {
            f[i]=1;
            continue;
        }
        else
        {
            f[i]=1+f[1];
            for(int j=2;j*j<=i;j++)
            {
                if(i%j!=0) continue;
                f[i]+=f[j];
                if(j*j!=i) f[i]+=f[i/j];
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        cout<<f[a[i]]<<' ';
    }
    return 0;
}