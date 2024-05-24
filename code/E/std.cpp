#include<iostream>

using namespace std;

constexpr int N = 2e5 + 10;
int n, m;
string s[N];
int ne[N], la[N];
bool book[N];

void solve() {
    for (int i = 1; i <= n; i++)
            ne[i] = i + 1, la[i] = i - 1;
    ne[n] = 1, la[1] = n;

    int sum = 0;
    for (int idx = 1; true; idx = ne[idx])
        for (int cnt = 1; true; cnt++) {
            if (!m--)
                return;

            string t;
            cin >> t;
            if (t == s[idx]) {
                if (cnt == 1) {
                    la[ne[idx]] = la[idx];
                    ne[la[idx]] = ne[idx];
                    book[idx] = true;
                    if (++sum == n)
                        return;
                }
                break;
            }
        }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    solve();

    for (int i = 1; i <= n; i++)
        if (book[i])
            cout << s[i] << "\n";
}