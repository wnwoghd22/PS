#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

typedef long long int ll;

ll dp[200001][3][2];
ll n;
std::vector<ll> v;

ll f(int i, ll h, int g, int b) {
	if (i == n) return 0;

	ll& ref = dp[i][g][b];
	if (~ref) return ref;

	ref = 0;
	ll a = v[i], ab = v[i] >> 1;

	if (a < h) ref = f(i + 1, h + ab, g, b) + 1;
	else if (a < h * 2) {
		if (g) ref = f(i + 1, h * 2 + ab, g - 1, b) + 1;
		if (b) ref = std::max(ref, f(i + 1, h * 3 + ab, g, b - 1) + 1);
	}
	else if (a < h * 3) {
		if (b) ref = f(i + 1, h * 3 + ab, g, b - 1) + 1;
		if (g == 2) ref = std::max(ref, f(i + 1, h * 4 + ab, g - 2, b) + 1);
	}
	else if (a < h * 4) {
		if (g == 2) ref = f(i + 1, h * 4 + ab, g - 2, b) + 1;
		if (g && b) ref = std::max(ref, f(i + 1, h * 6 + ab, g - 1, b - 1) + 1);
	}
	else if (a < h * 6) {
		if (g && b) ref = f(i + 1, h * 6 + ab, g - 1, b - 1) + 1;
	}
	else if (a < h * 12) {
		if (g == 2 && b) ref = f(i + 1, h * 12 + ab, g - 2, b - 1) + 1;
	}

	return ref;
}

int main() {
	int T;

	std::cin >> T;
	while (T--) {
		memset(dp, -1, sizeof dp);
		v.clear();
		ll h, i, a, result = 0;
		std::cin >> n >> h;
		for (i = 0; i < n; ++i) {
			std::cin >> a;
			v.push_back(a);
		}
		std::sort(v.begin(), v.end());

		result = f(0, h, 2, 1);

		std::cout << result << '\n';
	}
}