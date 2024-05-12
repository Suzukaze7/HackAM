#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pii1 pair<int,int>
#define pii2 pair<int,pair<int,int>>
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
//前四个是上右下左，后四个是右上右下左下左上.
int dx[9]={-1,0,1,0,-1,1,1,-1};
int dy[9]={0,1,0,-1,1,1,-1,-1};
int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a%b);
}
int quick(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=res*a;
        }
        a=a*a;
        b>>=1;
    }
    return res;
}
void solved(){
   cout<<"50";
}
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int __;
    __=1;
    while(__--){
        solved();
    }
     return 0;
}