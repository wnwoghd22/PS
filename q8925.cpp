#include <iostream>
#include <algorithm>

typedef long double ld;
const int LEN = 100'001;
const ld INF = 1e17;
const ld TOL = 1e-7;

int T, N, L, S[LEN];
char sq[LEN];

bool f(ld x) {
	ld min = 0;
	for (int i = 0, j = L; j <= N; ++i, ++j) {
		min = std::min(min, S[i] - x * i);
		if (S[j] - x * j > min - TOL)
			return 1;
	}
	return 0;
}

ld bs() {
	ld l = 0, r = 1, m;
	while (l < r - TOL) {
		m = (l + r) / 2;
		if (f(m)) l = m;
		else r = m;
	}
	return l;
}

ld t[LEN << 2];
void update(int x, ld d, int s = 0, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { t[i] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	t[i] = std::min(t[i << 1], t[i << 1 | 1]);
}
ld get(int l, int r, int s = 0, int e = N, int i = 1) {
	if (r < s || e < l) return INF;
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return std::min(get(l, r, s, m, i << 1), get(l, r, m + 1, e, i << 1 | 1));
}

int f(int bound, ld x) {
	int l = 0, r = bound, m, ret = 0;
	while (l <= r) {
		m = l + r >> 1;
		if (get(m, bound) < x + TOL) {
			ret = std::max(ret, m);
			l = m + 1;
		}
		else r = m - 1;
	}
	return ret;
}

void solve() {
	std::cin >> N >> L >> sq;
	for (int i = 0; i < N; ++i) S[i + 1] = S[i] + sq[i] - '0';
	ld rate = bs();
	// std::cout << rate << '\n';

	int l = -1, r = N + 2;
	ld min = 0;
	for (int i = 0, j = L, k; j <= N; ++i, ++j) {
		min = std::min(min, S[i] - rate * i);
		update(i, S[i] - rate * i);
		if (S[j] - rate * j < min - TOL) continue;
		k = f(i, S[j] - rate * j);
		if (j - k < r - l) l = k, r = j;
	}
	std::cout << l + 1 << ' ' << r << '\n';
}

int main() {
	std::cin >> T;
	while (T--) solve();
}