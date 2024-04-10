#include <iostream>

int s, N, K, R1, R2, C1, C2, m;
int len[11] = { 1, };

bool f(int r, int c, int t) {
	if (t == 0) return 1;
	int l = len[t - 1];
	if ((r / l < m || r / l >= N - m) || (c / l < m || c / l >= N - m)) return f(r % l, c % l, t - 1);
	return 0;
}

int main() {
	std::cin >> s >> N >> K >> R1 >> R2 >> C1 >> C2;
	m = (N - K) / 2;
	for (int i = 1; i <= 10; ++i) len[i] = len[i - 1] * N;
	for (int r = R1; r <= R2; ++r) {
		for (int c = C1; c <= C2; ++c)
			std::cout << !f(r, c, s);
		std::cout << '\n';
	}
}