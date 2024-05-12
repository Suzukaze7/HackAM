#include<bits/stdc++.h>
using namespace std;
 int n;
 int main() {
    cin >> n;
    vector<int> a(n);
    for (int &i : a)cin >> i;
    int s = accumulate(a.begin(), a.end(), 0);
    cout << max(0, s - 50) << "\n";
    return 0;
}