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

ld val[LEN];
int sp, idx[LEN];

int g(ld x) {
	int l = 0, r = sp - 1, m, ret = 0;
	while (l <= r) {
		m = l + r >> 1;
		if (val[m] < x + TOL) {
			ret = std::max(ret, m);
			l = m + 1;
		}
		else r = m - 1;
	}
	return idx[ret];
}

void solve() {
	std::cin >> N >> L >> sq;
	for (int i = 0; i < N; ++i) S[i + 1] = S[i] + sq[i] - '0';
	ld rate = bs();

	val[0] = idx[0] = 0; sp = 1;
	int l = -1, r = N + 2;
	for (int i = 0, j = L, k; j <= N; ++i, ++j) {
		while (sp && val[sp - 1] > S[i] - rate * i - TOL) --sp;
		val[sp] = S[i] - rate * i; idx[sp] = i; ++sp;
		if (S[j] - rate * j < val[0] - TOL) continue;
		k = g(S[j] - rate * j);
		if (j - k < r - l) l = k, r = j;
	}
	std::cout << l + 1 << ' ' << r << '\n';
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) solve();
}