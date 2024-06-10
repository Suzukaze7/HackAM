#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int N = 2e5 + 100;

string s1[N], s2[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;

    set<int> S;

    for(int i = 0; i < n; i ++)
        cin >> s1[i], S.insert(i);
    for(int i = 0; i < m; i ++)
        cin >> s2[i];

    set<int> ans;
    bool flag = false;
    for(int i = 0, j = 0; i < m; i ++)
    {
        if(s2[i] == s1[j])
        {
            if(!flag)
                ans.insert(j), S.erase(j);
            else
                flag = false;

            if(!S.size())
                break;

            if(*S.rbegin() >= j + 1)
                j = *S.lower_bound(j + 1);
            else
                j = *S.begin();
        }
        else
            flag = true;
    }

    for(int x : ans)
        cout << s1[x] << '\n';

}