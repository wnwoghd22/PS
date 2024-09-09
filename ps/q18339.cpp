#include <iostream>

typedef long long ll;
const int LEN = 100'001;
const ll INF = 2e9 + 7;

int N, S, H[LEN], X[LEN];

struct SegMax {
	int t[LEN << 2];
	ll A[LEN + 2];
	void update(int x, ll d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { A[s] = d; t[i] = s; return; }
		int m = s + e >> 1, _l = i << 1, _r = i << 1 | 1;
		update(x, d, s, m, _l);
		update(x, d, m + 1, e, _r);
		t[i] = A[_r] > A[_l] ? _r : _l;
	}
	int get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return N + 1;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		int _l = get(l, r, s, m, i << 1);
		int _r = get(l, r, m + 1, e, i << 1 | 1);
		return A[_r] > A[_l] ? _r : _l;
	}
} L, R;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> S;
	for (int i = 1; i <= N; ++i) {
		std::cin >> X[i] >> H[i];
		L.update(N + 1 - i, H[i] + X[i] + INF);
		R.update(i, H[i] - X[i] + INF);
	}
	L.A[N + 1] = R.A[N + 1] = INF;
	L.update(N + 1 - S, 0);
	R.update(S, 0);
	ll ret = 0;
	for (int q = 1, l, r, x = S; q < N; ++q) {
		l = L.get(N + 1 - x, N);
		r = R.get(x, N);
		std::cout << l << ' ' << r << '\n';
		if (l > N) l = N + 1 - r;
		else if (r > N) r = N + 1 - l;
		else if (R.A[r] + X[x] > L.A[l] - X[x]) l = N + 1 - r;
		else r = N + 1 - l;
		
		std::cout << r << '\n';
		L.update(l, 0);
		R.update(r, 0);
		ret += std::abs(X[x] - X[r]);
		x = r;
	}
	std::cout << ret;
}