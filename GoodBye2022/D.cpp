#include <iostream>
#include <algorithm>

typedef long long int ll;
ll T, a, b, c, k, n, max, min;

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> a >> b >> c >> n >> k;
		ll i = k - 1, j = n - k;
		if (a == b && b == c) {
			max = min = b * (n - 1);
		}
		else if (b >= a && b >= c) {
			max = b * (n - 1);
			min = (j & 1) * std::min(a, c) + (j >> 1) * std::min(a + c, 2 * b) + i * std::min(a, c);
		}
		else if (b <= a && b <= c) {
			min = b * (n - 1);
			max = (i & 1) * std::max(a, c) + (i >> 1) * std::max(a + c, 2 * b) + j * std::max(a, c);
		}
		else {
			max = (i & 1) * b + (i >> 1) * std::max(a + c, 2 * b) + j * std::max(a, c);
			min = (j & 1) * b + (j >> 1) * std::min(a + c, 2 * b) + i * std::min(a, c);
		}
		std::cout << max << ' ' << min << '\n';
	}
}