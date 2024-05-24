#include<iostream>

using namespace std;

constexpr int N = 2e5 + 10;
int n, k;
int a[N];
bool book[3];

int get(int k) {
    if (k > n)
        return k - n;
    if (k < 1)
        return k + n;
    return k;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        book[0] |= a[i] == get(i - 1);
        book[1] |= a[i] == get(i);
        book[2] |= a[i] == get(i + 1);
    }

    if (k == 1)
        cout << (book[1] ? "Yes" : "No");
    else
        cout << (book[1] && (book[0] || book[2]) ? "Yes" : "No");
}