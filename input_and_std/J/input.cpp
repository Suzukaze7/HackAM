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
#define debug(args...)0
#define debug_n(a,n)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll=long long;

#include<random>
mt19937 rng(random_device{}());
int rdi(int l,int r) {
    return rng()%(r-l+1)+l;
}

constexpr int N = 2e5 + 10;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n  = rdi(1, 8);
    cout<<n<<"\n";
    for(int i=0; i<n; ++i) {
        cout<<rdi(1, 10)<<' ';
    }
    return 0;
}
/*




*/