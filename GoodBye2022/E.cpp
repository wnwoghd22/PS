#include <iostream>
#include <algorithm>

typedef long long int ll;
ll T, a, b, c, k, n, max, min;
inline ll f(ll x, ll y) { return (x & 1 ? (x >> 1) * (a + c) : ((x >> 1) - 1) * (a + c) + y); }
inline ll g(ll x) { return (x - 1) * b; }

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> a >> b >> c >> n >> k;
		if (a < c) ll temp = a, a = c, c = temp;

		if (c <= b && b <= (a + c) / 2) {
			max = (n - k) * a + f(k, b);
			min = (k - 1) * c + g(n - k + 1);
		}
		else if ((a + c) / 2 < b && b <= a) {
			max = (n - k) * a + g(k);
			min = (k - 1) * c + f(n - k + 1, b);
		}
		else if (b <= c) {
			max = (n - k) * a + f(k, c);
			min = (n - 1) * b;
		}
		else if (a <= b) {
			max = (n - 1) * b;
			min = (k - 1) * c + f(n - k + 1, a);
		}
		std::cout << max << ' ' << min << '\n';
	}
}