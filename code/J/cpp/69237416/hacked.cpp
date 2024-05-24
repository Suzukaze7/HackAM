#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    int sum = 0;
    cin >> n;
    for(int i = 0; i < n; i ++){
        int x;
        cin >> x;
        sum += x;
    }
    cout << max(0,sum-50);
    return 0;
}