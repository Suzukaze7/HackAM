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
int a[2];
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,i,x;
    cin>>n;
    for(i=0;i<n;++i)
    {
        cin>>x;
        ++a[x&1];
    }
    if(a[1]&1)
        cout<<"-1";
    else
        cout<<a[0]+a[1]/2;
    return 0;
}