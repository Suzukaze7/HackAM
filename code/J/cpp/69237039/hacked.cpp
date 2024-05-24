#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++) {
        int x;cin>>x;
        sum+=x;
    }
    if(sum<=50) cout<<0<<endl;
    else cout<<sum-50<<endl;
}