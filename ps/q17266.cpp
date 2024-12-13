#include <iostream>

const int LEN = 100'001;
int N, M, x[LEN];

int f(int m) {
	int cur = 0;
	for (int i = 0; i < M; ++i) {
		if (cur < x[i] - m) return 0;
		cur = x[i] + m;
	}
	return cur >= N;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) std::cin >> x[i];
	int l = 1, r = N, m, ret = N;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m)) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	std::cout << ret;
}