#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
#include<string>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<vector>
#include<set>
#include<unordered_set>
#include<bitset>
#include<climits>
#include<numeric>
#include<functional>
#include<iomanip>
#ifdef YJL
#include<debug.h>
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

constexpr int N = 2e5 + 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    assert(1<=n and n<=100);
    vector<int> a(n);
    ll sum = 0;
    int num[2]{};
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        assert(0<=a[i] and a[i]<=100);
        sum += a[i];
        num[a[i]%2]++;
    }
    if(sum%2 == 1) {
        cout<<"-1\n";
    }else {
        cout<<num[0]+num[1]/2<<"\n";
    }
    return 0;
}
/*




*/