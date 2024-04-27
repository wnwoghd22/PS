#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 4e5;

int N;

struct SegSum {
	ll t[LEN << 2];
	void update(int x, ll d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) {
			t[i] += d;
			return;
		}
		int m = s + e >> 1;
		update(x, d, s, m, i << 1);
		update(x, d, m + 1, e, i << 1 | 1);
		t[i] = t[i << 1] + t[i << 1 | 1];
	}
	ll get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
	}
} sum, cnt;

struct E {
	int a, i;
	bool operator<(const E& r) const {
		return a < r.a;
	}
} arr[LEN];

int A[LEN], order[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		arr[i].a = A[i];
		arr[i].i = i;
	}
	std::sort(arr, arr + N);

	int ord = 1;
	order[arr[0].i] = ord;
	for (int i = 1; i < N; ++i) {
		if (arr[i].a != arr[i - 1].a) ord++;
		order[arr[i].i] = ord;
	}

	// for (int i = 0; i < N; ++i) std::cout << order[i] << ' ';
	// std::cout << '\n';

	ll ret = 0;
	for (int i = 0; i < N; ++i) {
		int x = order[i];
		ll S = sum.get(1, x - 1);
		ll C = cnt.get(1, x - 1);
		ret += C * A[i] - S;
		sum.update(x, A[i]);
		cnt.update(x, 1);
	}
	std::cout << ret;
}