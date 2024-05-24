#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int ans = 0, cnt = 0;

    while(n --)
    {
        int m;
        cin >> m;

        if(m % 2)
            cnt ++;
        else
            ans ++;
    }

    if(cnt % 2 == 0)
        cout << ans + cnt / 2;
    else
        puts("-1");
}