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

	if (v[i] < h) ref = f(i + 1, h + v[i] / 2, g, b) + 1;
	else if (v[i] < h * 2) {
		if (g) ref = f(i + 1, h * 2 + v[i] / 2, g - 1, b) + 1;
		if (b) ref = std::max(ref, f(i + 1, h * 3 + v[1] / 2, g, b - 1) + 1);
	}
	else if (v[i] < h * 3) {
		if (b) ref = f(i + 1, h * 3 + v[i] / 2, g, b - 1) + 1;
		if (g == 2) ref = std::max(ref, f(i + 1, h * 4 + v[i] / 2, g - 2, b) + 1);
	}
	else if (v[i] < h * 4) {
		if (g == 2) ref = f(i + 1, h * 4 + v[i] / 2, g - 2, b) + 1;
		if (g && b) ref = std::max(ref, f(i + 1, h * 6 + v[i] / 2, g - 1, b - 1) + 1);
	}
	else if (v[i] < h * 6) {
		if (g && b) ref = f(i + 1, h * 6 + v[i] / 2, g - 1, b - 1) + 1;
	}
	else if (v[i] < h * 12) {
		if (g == 2 && b) ref = f(i + 1, h * 12 + v[i] / 2, g - 2, b - 1) + 1;
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