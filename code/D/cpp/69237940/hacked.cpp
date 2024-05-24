#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
void solve()
{
    int n,k;cin>>n>>k;
    vector<int>a(n+1);
    map<int,int>mp;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[(a[i]-i+n)%n]++;
    }
    for(int i=0;i<k;i++){
        if(mp[i]<=0){cout<<"No"<<endl;return;}
    }
    cout<<"Yes"<<endl;

    

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tt = 1;
	//cin>>tt;
	while(tt--) solve();
	return 0;
}