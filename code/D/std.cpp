#include<iostream>

using namespace std;

constexpr int N = 2e5 + 10;
int n, k;
bool book[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        book[(x - i + n) % n] = true;
    }

    for (int i = 0; i < k; i++)
        if (!book[i]) {
            cout << "No";
            return 0;
        }
    cout << "Yes";
}