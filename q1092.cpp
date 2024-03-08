#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 1e4 + 1;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return -1;
	if (a > b) std::swap(a, b);
	p[a] += p[b];
	return p[b] = a;
}

int N, C[50], M, W[LEN];
int bs(int w) {
	int l = 0, r = M, m, i = 0;
	while (l <= r) {
		m = l + r >> 1;
		if (W[m] <= w) {
			i = std::max(i, m);
			l = m + 1;
		}
		else r = m - 1;
	}
	return i;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> C[i];
	std::sort(C, C + N);
	
	std::cin >> M;
	for (int i = 1; i <= M; ++i) std::cin >> W[i];
	std::sort(W, W + M + 1);

	if (W[M] > C[N - 1]) {
		std::cout << -1;
		return 0;
	}
	memset(p, -1, sizeof p);
	int cnt = 0, t = 0;
	while (cnt < M) {
		for (int i = N - 1, j; i >= 0; --i) {
			if (j = find(bs(C[i]))) {
				++cnt;
				join(j, j - 1);
			}
		}
		++t;
	}
	std::cout << t;
}