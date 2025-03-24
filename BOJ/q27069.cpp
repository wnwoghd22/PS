#include <iostream>
#include <algorithm>

typedef long long int ll;
ll T, a, b, c, d, e, k, n, max, min;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::cin >> a >> b >> c >> n >> k;
		d = n - k, e = k - 1;
		if (a < c) std::swap(a, c);

		if (c <= b && b * 2 <= a + c) {
			max = d * a + e / 2 * (a + c) + b * (e & 1);
			min = e * c + d * b;
		}
		else if (a + c <= b * 2 && b <= a) {
			max = d * a + e * b;
			min = e * c + d / 2 * (a + c) + b * (d & 1);
		}
		else if (b <= c) {
			max = d * a + e / 2 * (a + c) + c * (e & 1);
			min = (n - 1) * b;
		}
		else if (a <= b) {
			max = (n - 1) * b;
			min = e * c + d / 2 * (a + c) + a * (d & 1);
		}
		std::cout << max << ' ' << min << '\n';
	}
}