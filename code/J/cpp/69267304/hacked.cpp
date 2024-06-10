#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	int n;
	cin >> n;

	assert(1 <= n && n <= 10);

	int ans = 0;
	while(n --)
	{
		int x;
		cin >> x;

		assert(1 <= x && x <= 10);

		ans += x;
	}

	if(ans <= 50)
		puts("0");
	else
		cout << ans - 50;
	
	return 0;


}