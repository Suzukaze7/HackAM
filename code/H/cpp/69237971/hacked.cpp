#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
#define int long long 
int n;
int a[N];
int f[N];
signed main(){
    cin >> n;
    f[1] = 1,f[2] = 2;
    for(int i = 3; i <= 1e5; i ++){
        //f[i] = 2;
        for(int j = 1; j * j <= i; j ++){
            if(i % j == 0){
                int x = j,y = i/j;
                f[i] += f[x];
                if(x != y) f[i] += f[y];
            }
        }
    }
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        cout << f[x] << ' ';
    }
    
    return 0;
}