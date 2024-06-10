#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

const int N = 1e5;

int f[N+1];

int main(){
    for(int i = 1; i <= N; i ++ ){
        f[i] ++;
        for( int j = i+i; j <= N; j += i) 
            f[j] += f[i];
    }
    int n;
    cin >> n;
    for(int i = 1, x; i <= n ; i ++)
        cin >> x, cout << f[x]<< " ";
    return 0;
}