#include <iostream>

using namespace std;

const int N = 2e5 + 100;

int a[N], b[N], c[N];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    bool has_anser = false;

    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);

        if(a[i] == i)
            has_anser = true;
    }

    if(!has_anser)
    {
        puts("No");
        return 0;
    }

    int ans = 1;

    for(int i = 1; i <= n; i ++)
        b[i % n + 1] = a[i], c[(i - 1) % n ? (i - 1) % n : n] = a[i];

    // for(int i = 1; i <= n; i ++)
    // {
    //     clog << b[i] << " ";
    // }
    // clog << '\n';

    // for(int i = 1; i <= n; i ++)
    // {
    //     clog << c[i] << " ";
    // }
    // clog << '\n';



    bool flag = false;
    for(int i = 1; i <= n; i ++)
        if(i == b[i] || i == c[i])
        {
            flag = true;
            break;
        }

    if(flag)    ans = 1e9;

    puts(ans >= k ? "Yes" : "No");




}