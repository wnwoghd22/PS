#include <iostream>

typedef long long ll;
const int LEN = 500'001;

int N, A[LEN], ret[LEN];
ll K;

struct MinSeg {
	int t[LEN << 2];
	void update(int x, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { t[i] = s; return; }
		int m = s + e >> 1;
		update(x, s, m, i << 1); update(x, m + 1, e, i << 1 | 1);
		t[i] = A[t[i << 1]] > A[t[i << 1 | 1]] ? t[i << 1 | 1] : t[i << 1];
	}
	int get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		int _l = get(l, r, s, m, i << 1);
		int _r = get(l, r, m + 1, e, i << 1 | 1);
		return A[_l] > A[_r] ? _r : _l;
	}
} min;

struct CntSeg {
	int t[LEN << 2];
	void update(int x, int d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { t[i] += d; return; }
		int m = s + e >> 1;
		update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
		t[i] = t[i << 1] + t[i << 1 | 1];
	}
	int ord(int k, int s = 1, int e = N, int i = 1) {
		if (s == e) return s;
		int m = s + e >> 1;
		if (t[i << 1] >= k) return ord(k, s, m, i << 1);
		return ord(k - t[i << 1], m + 1, e, i << 1 | 1);
	}
	int cnt(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return cnt(l, r, s, m, i << 1) + cnt(l, r, m + 1, e, i << 1 | 1);
	}
} cnt;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	A[0] = 1e9 + 7;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		min.update(i);
		cnt.update(i, 1);
	}
	for (int i = 0; i < N; ++i) {
		int r = K + 1 < N - i ? cnt.ord(K + 1) : N;
		int x = min.get(1, r);
		ret[i] = A[x];
		K -= cnt.cnt(1, x - 1);
		A[x] = 1e9 + 7;
		min.update(x);
		cnt.update(x, -1);
	}
	if (K & 1) {
		bool same = 0;
		for (int i = 0; i < N - 1; ++i) {
			if (ret[i] == ret[i + 1]) {
				same = 1;
				break;
			}
		}
		if (!same) {
			std::swap(ret[N - 2], ret[N - 1]);
		}
	}

	for (int i = 0; i < N; ++i) std::cout << ret[i] << ' ';
}