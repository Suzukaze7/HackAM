#include<iostream>
#include<vector>
using namespace std;
constexpr int N = 2e5 + 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    int sum = 0;
    int num[2]{};
    for(int i=0; i<n; ++i) {
        cin>>a[i];
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
