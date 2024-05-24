#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k;
int a[N];
int main(){
    cin >> n >> k;
    int res1 = 0,res2 = 0,res3 = 0,f = 0;
    for(int i = 1; i <= n;i ++){
        cin >> a[i];
        if(a[i] == i){
            res1 ++;
        } 
        if(a[i] == i - 1) res2 ++;
        if(a[i] == i + 1) res3 ++;
    }
    if(a[1] == n) res2 ++;
    if(a[n] == 1) res3 ++;
    for(int i = 1; i <= n; i ++){
        if(a[i] == i){
            if(a[i] == a[i - 1] || a[i + 1] == a[i]) f = 1;
        } 
    }
    if((a[1] == 1 && a[n] == a[1]) || (a[n] == n && a[n] == a[1])) f = 1;
    if(k == 1){
        if(res1) cout <<"Yes";
        else cout << "No";
        return 0;
    }
    if(f){
        cout << "Yes";
        return 0;
    }
    if(res1 > 0 && (res2 || res3)) cout << "Yes";
    else cout << "No";
    return 0;
}