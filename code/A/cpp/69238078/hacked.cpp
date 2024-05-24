//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
//#define int long long
typedef pair<int, int> PII;

int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0}; //L R D U
int n, m;
string str;
const int N = 1010;
char ma[N][N];
int f[N][N][4];
bool st[N][N];

void solve() {
	cin >> n >> m;
	int stx = 0, sty = 0, enx = 0, eny = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> ma[i][j];
			if (ma[i][j] == 'S')stx = i, sty = j;
			if (ma[i][j] == 'T')enx = i, eny = j;
		}
	for (int i = 1; i <= n; i++) {
		bool ok = false;
		int l = -1;
		for (int j = 1; j <= m; j++) {
			if (ma[i][j] != '#') {
				if (!ok)ok = true, l = j;
				f[i][j][0] = l;
			} else {
				ok = false;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		bool ok = false;
		int l = -1;
		for (int j = m; j >= 1; j--) {
			if (ma[i][j] != '#') {
				if (!ok)ok = true, l = j;
				f[i][j][1] = l;
			} else {
				ok = false;
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		bool ok = false;
		int l = -1;
		for (int j = 1; j <= n; j++) {
			if (ma[j][i] != '#') {
				if (!ok)ok = true, l = j;
				f[j][i][2] = l;
			} else {
				ok = false;
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		bool ok = false;
		int l = -1;
		for (int j = n; j >= 1; j--) {
			if (ma[j][i] != '#') {
				if (!ok)ok = true, l = j;
				f[j][i][3] = l;
			} else {
				ok = false;
			}
		}
	}
//	for (int i = 1; i <= n; i++)
//		for (int j = 1; j <= m; j++) {
//			cout << i << " " << j << ":\n";
//			for (int k = 0; k <= 3; k++) {
//				cout << f[i][j][k] << " \n"[k == 3];
//			}
//		}
	queue<tuple<int, int, int>> q;
	q.push({stx, sty, 0});
	st[stx][sty] = true;
	while (q.size()) {
		auto [x, y, z] = q.front();
		q.pop();
//		cout << x << " " << y << "-\n";
		if (x == enx && y == eny) {
			cout << z << "\n";
			return ;
		}
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			if (i == 0 || i == 1)nx = x, ny = f[x][y][i];
			if (i == 2 || i == 3)nx = f[x][y][i], ny = y;
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !st[nx][ny]) {
				q.push({nx, ny, z + 1});
				st[nx][ny] = true;
			}
		}
	}
	cout << "-1\n";
}

signed main() {
	IOS
	int T = 1;
	//	cin>>T;
	while (T--) solve();

	return 0;
}