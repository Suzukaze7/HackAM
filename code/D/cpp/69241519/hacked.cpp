#include <bits/stdc++.h>

using namespace std ;

int main()
{
    cin.tie(nullptr)->ios::sync_with_stdio(false) ;
    int n , k ;
    cin >> n >> k ;
    std::vector<int> a(n + 10 , 0) ;
    set<int> s ;
    for(int i = 0 ; i <= n ; ++ i) s.insert(i) ;
    for(int i = 1 ; i <= n ; ++ i)
    {
        int x ;
        cin >> x;
        a[i] = ((x - i) % n + n) % n ;
        if ( s.count(a[i]) ) s.erase(a[i]) ;
    }
    if ( *s.begin() >= k ) cout << "Yes\n" ; 
    else cout << "No\n" ;
    
    return 0 ;
}