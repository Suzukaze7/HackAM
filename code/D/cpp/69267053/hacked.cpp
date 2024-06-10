#include <iostream>
#include <cassert>

using namespace std;

const int N = 2e5 + 100;

int a[N];
bool st[N];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    assert(1 <= n && n <= 2e5);
    assert(1 <= k && k <= 2e5);

    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);

        assert(1 <= a[i] && a[i] <= 2e5);

        if(a[i] >= i)
            st[a[i] - i] = true;
        else
            st[a[i] + n - i] = true;
    }

    bool has_anser = true;
    for(int i = 0; i < n && i < k; i ++)
        if(!st[i])
        {
            has_anser = false;
            break;
        }

    puts(has_anser ? "Yes" : "No");









}