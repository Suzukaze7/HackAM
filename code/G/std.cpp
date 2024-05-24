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

template<typename Int>
struct SparseTable {
    vector<vector<int>> f;
    vector<Int> a;
    function<bool(Int,Int)> better;
    SparseTable(const vector<Int>& a, function<bool(Int,Int)> better)
    : a(a), better(better), f(a.size(),vector<int>(__lg(a.size())+1)) {
        int n=a.size(), lg=__lg(n);
        for(int i=0; i<n; ++i)
            f[i][0]=i;
        for (int k=1; k<=lg; ++k)
            for (int i=0; i+(1<<k)-1<n; ++i) {
                int l=f[i][k-1],r=f[i+(1<<(k-1))][k-1];
                f[i][k]=(better(a[l],a[r])?l:r);
            }
    }
    int queryIndex(int l,int r) {
        int k=__lg(r-l+1);
        int i=f[l][k],j=f[r-(1<<k)+1][k];
        return better(a[i],a[j])?i:j;
    }
    Int queryValue(int l,int r) {
        return a[queryIndex(l,r)];
    }
};

map<int,vector<int>> id;
int count_val(int val, int l, int r) {
    auto& v = id[val];
    return upper_bound(ALL(v),r)-lower_bound(ALL(v),l);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n,q;
    cin>>n>>q;
    assert(n>=1 and n<=2e5);
    assert(q>=1 and q<=2e5);

    vector<int> a(n), up(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        assert(a[i]>=1 and a[i]<=1e9);
        id[a[i]].push_back(i);
        up[i] = i;
        if(i and a[i-1]>=a[i]) {
            up[i] = up[i-1];
        }
    }

    SparseTable<int> sp(a, [&](int x,int y){return x<=y;});

    while(q--) {
        int l,r;
        cin>>l>>r;
        assert(l>=1 and l<=n);
        assert(r>=1 and r<=n);
        --l, --r;

        int p = sp.queryIndex(l,r);// p = min_element(a+l, a+r+1)-a
        if(up[r] <= p) {// a[p]=a[p+1]=...=a[r]
            int u = max(l, up[p]);
            if(u == l) {
                cout << "0\n";
                continue;
            }
            int i0 = sp.queryIndex(l, u-1);
            int k = lower_bound(a.begin()+u, a.begin()+p+1, a[i0], greater<int>())-a.begin();
            int remain = count_val(a[i0], l, u-1) + (r-k+1);
            cout << r-l+1 - remain <<"\n";
        }else {
            // 最小值被保留
            cout << r-l+1 - count_val(a[p], l, r) <<"\n";
        }
    }
    return 0;
}
/*




*/