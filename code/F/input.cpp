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
#include<fstream>
#ifdef YJL
#include<debug.h>
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

#include<random>
mt19937_64 rng(random_device{}());
ll rdi(ll l, ll r) {
    return rng() % (r-l+1) + l;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n = rdi(1, 10);
    cout<<n<<'\n';
    for(int i=1; i<=n; ++i) {
        cout<<rdi(0, 10)<<" \n"[i==n];
    }
    return 0;
}
/*




*/