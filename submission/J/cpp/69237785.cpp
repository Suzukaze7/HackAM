#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <bitset>
using namespace std;
using ll=long long;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll sum=0;
    int n,i,x;
    cin>>n;
    for(i=0;i<n;++i)
    {
        cin>>x;
        sum+=x;
    }
    if(sum<50)
        cout<<"0";
    else
        cout<<sum-50;
    return 0;
}