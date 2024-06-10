#include<bits/stdc++.h>
using namespace  std;
typedef long long ll;
const int N=2e5+10;
int ne[N],la[N];
bool st[N];
void solve()
{
	int n,m;
	cin>>n>>m;
	string s[N];
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        ne[i]=i+1;
        la[i]=i-1;
    }
    ne[n]=1;
    la[1]=n;
    int sum=0;
	for(int i=1;i;i=ne[i])
	{
        if(sum==m) break;
		for(int j=1;1;j++)
        {
            string t;
            cin>>t;
            sum++;
            if(t==s[i])
            {
                if(j==1)
                {
                    ne[la[i]]=ne[i];
                    la[ne[i]]=la[i];
                    st[i]=1;
                }
                break;
            }
            if(sum==m) break;
        }
	}
	for(int i=1;i<=n;i++)
    {
        if(st[i])
        {
            cout<<s[i]<<endl;
        }
    }
}
int main()
{
	int t;
	t=1;
	while(t--)
	{
	solve();
	}
	return 0;
}
