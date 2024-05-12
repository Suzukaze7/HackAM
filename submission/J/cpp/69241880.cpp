#include <bits/stdc++.h>
 using namespace std;
 using vi = vector<int>;
 const int inf = 1e9;
const int dx[] = {0, 0, -1, 1} , dy[] = {1, -1, 0, 0};
  int main(){
    int n, sum = 0;
    cin >> n;
    for(int i = 1, x; i <= n; i ++)
        cin >> x, sum += x;
    cout << max(0, sum - 50) << "\n";
    return 0;
}