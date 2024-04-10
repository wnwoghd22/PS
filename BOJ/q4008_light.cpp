#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 1'000'001;
ll N, A, B, C, x, dp[LEN], S[LEN];
inline ll f(ll x) { return A * x * x + B * x + C; }
inline ll fa(int x) { return -2 * A * S[x]; }
inline ll fb(int x) { return A * S[x] * S[x] - B * S[x] + dp[x]; }

int hull[LEN], _size, ptr;
ld xpos[LEN];
ld intersect(int r, int l) {
	ld a1 = fa(r), b1 = fb(r);
	ld a2 = fa(l), b2 = fb(l);
	return (b1 - b2) / (a2 - a1);
}

void add_line(int n) {
	if (!_size) {
		hull[++_size] = n;
		xpos[_size] = -INF;
		return;
	}
	while (_size > 1 && xpos[_size] > intersect(hull[_size], n)) --_size;
	hull[++_size] = n;
	xpos[_size] = intersect(hull[_size - 1], n);
	if (ptr > _size) ptr = _size;
}

int main() {
	std::cin >> N >> A >> B >> C;
	for (int i = 1; i <= N; ++i) {
		std::cin >> x;
		S[i] = S[i - 1] + x;
	}
	for (int n = 1; n <= N; ++n) {
		dp[n] = f(S[n]);
		if (_size) {
			while (ptr < _size && xpos[ptr + 1] < S[n]) ++ptr;
			int i = hull[ptr];
			dp[n] = std::max(dp[n], dp[i] + f(S[n] - S[i]));
		}
		add_line(n);
	}
	std::cout << dp[N];
}