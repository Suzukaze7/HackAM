#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];
int n,k;
int st[N];
int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        if(a[i] - i >= 0){
            st[a[i] - i] = 1;
        }else{
            st[n - i + a[i]] = 1;
        }
    }
    int res = 0;
    for(int i = 0; i <= n; i ++){
        if(st[i]){
            res ++;
        }else break;
    }
    if(res >= k) cout << "Yes";
    else cout << "No";
    return 0;
}