//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define de(a) cout << #a << " = " << a << "\n";
#define deg(a) cout << #a << " = " << a << " ";
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define int long long
#define lowbit(x)  ((x) & - (x))
#define LF(x)   fixed<<setprecision(x)
//vector<vector<int>> ma((n+10),vector<int>(m+10));
typedef pair<int, int> PII;
const double pi = acos(-1.);

int qmi(int a, int b, int q) {
	int res = 1 % q;
	while (b) {
		if (b & 1)res = res * a % q;
		a = a * a % q;
		b >>= 1;
	}
	return res;
}
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0}; //L R D U
int n, m;
string str;
const int N = 110;
int c[N], ans, ji, ou;

void solve() {
	cin >> n;
	for (int i = 1, x; i <= n; i++) {
		cin >> x;
		if (!x)ans++;
		else if (x & 1)ji++;
		else ou++;
	}
	if (ji & 1)cout << -1;
	else cout << ji / 2 + ou + ans;
}

signed main() {
	IOS
	int T = 1;
	//	cin>>T;
	while (T--) solve();

	return 0;
}