#include <iostream>

const int LEN = 1'000'001;

char seq[LEN];
int N, S[LEN];

int query(int k) {
	int result = 0;
	int l, r, m, d, x, c, s, i = 0;
	while (true) {
		d = N - i;
		if (d < k) break;
		if (d == k) {
			result++;
			break;
		}
		l = 0, r = d / k, x = N;
		// std::cout << "range: " << i << ' ' << l << ' ' << r << '\n';
		while (l <= r) {
			m = l + r >> 1;
			s = S[i + (m + 1) * k] - S[i];
			if (s) {
				x = std::min(x, m);
				r = m - 1;
			}
			else l = m + 1;
		}
		// std::cout << "find " << k << ' ' << i << ' ' << x << '\n';
		c = S[i + (x + 1) * k] - S[i + x * k];
		// std::cout << c << '\n';
		result += x + 1;
		i += k * (x + 1);
		k -= c;
		// std::cout << k << '\n';
		if (!k) break;
	}
	return result;
}

int main() {
	std::cin >> N >> seq;
	for (int i = 0; i < N; ++i) S[i + 1] = S[i] + (seq[i] == 'S');
	for (int k = 1; k <= N; ++k) std::cout << query(k) << ' ';
}