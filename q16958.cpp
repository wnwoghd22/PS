#include <iostream>

const int LEN = 1001;
const int INF = 3000;

int N, M, T, A, B;
int s[LEN], x[LEN], y[LEN];
int _p[2], _s[2][LEN];
int d[LEN];

int main() {
	std::cin >> N >> T;

	for (int i = 1; i <= N; ++i) {
		std::cin >> s[i] >> x[i] >> y[i];
		d[i] = s[i] ? 0 : INF;
		_s[s[i]][_p[s[i]]++] = i;
	}
	for (int p0 = 0, u; p0 < _p[0]; ++p0) {
		u = _s[0][p0];
		for (int p1 = 0, v; p1 < _p[1]; ++p1) {
			v = _s[1][p1];
			d[u] = std::min(d[u], abs(x[v] - x[u]) + abs(y[v] - y[u]));
		}
	}
	std::cin >> M;
	while (M--) {
		std::cin >> A >> B;
		std::cout << std::min(abs(x[A] - x[B]) + abs(y[A] - y[B]), d[A] + T + d[B]) << '\n';
	}
}
