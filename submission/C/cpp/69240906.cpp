#include <bits/stdc++.h>
 using namespace std ;
 int main()
{
    cin.tie(nullptr)->ios::sync_with_stdio(false) ;
    int n , k ;
    cin >> n >> k ;
    set<int> s ;
    for(int i = 0 ; i <= n ; ++ i) s.insert(i) ;
    for(int i = 1 ; i <= n ; ++ i)
    {
        int x ;
        cin >> x;
        int l = ((x - i) % n + n) % n ;
        int r = ((i - x) % n + n) % n ;
        if ( s.count(l) ) s.erase(l) ;
        if ( s.count(r) ) s.erase(r) ;
    }
    if ( *s.begin() >= min(2 , n) ) cout << "Yes\n" ; 
    else cout << "No\n" ; 
         return 0 ;
}