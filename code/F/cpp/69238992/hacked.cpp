#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 1e5+10;
int f[N];
signed main() {
    for(int i=1;i<N;i++) {
        f[i]++;
        for(int j=i+i;j<N;j+=i) f[j]+=f[i];
    }
    int n;cin>>n;
    for(int i=1;i<=n;i++) {
        int x;cin>>x;
        cout<<f[x]<<" ";
    }
}