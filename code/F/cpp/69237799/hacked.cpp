/*
* @Author: xucheng
* @Date: 2024-05-07 19:30
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <cmath>

#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define debug(x) cout << "debug: " << #x << " = " << x << "\n";

using namespace std;
using PII = pair<int, int>;

int n;
const int N = 100;
int a[N];

void solve()
{
    cin >> n;
    int ans = 0, res = 0;
    for (int i = 1; i <= n; i ++ ) {
        cin >> a[i];
        a[i] %= 2;
        if(a[i] == 1) {
            res ++;
        } else {
            ans ++;
        }
    }
    if(res % 2) {
        cout << "-1\n";
    } else {
        cout << ans + res / 2 << "\n";
    }
}

signed main()
{
    std :: ios :: sync_with_stdio(false);
    std :: cin.tie(nullptr), std :: cout.tie(nullptr);

    int test = 1;
    // cin >> test;

    while( test -- )
    {
        solve();
    }

    return 0;
}