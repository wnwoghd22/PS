#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>

typedef long long int ll;
const int MAX = 100'001;
const ll MOD = 1e9 + 7;
ll A[MAX];

int N, M, K;

namespace sum {
	ll segTree[MAX * 4];

	void update_diff(int left, int right, ll diff, int index = 1, int start = 1, int end = N) {
		if (left > end || right < start) return;
		if (start == end || left <= start && end <= right) {
			segTree[index] += diff; return;
		}
		int mid = (start + end) / 2;
		update_diff(left, right, diff, index * 2, start, mid);
		update_diff(left, right, diff, index * 2 + 1, mid + 1, end);
	}

	ll get_diff(int n, int start = 1, int end = N, int index = 1) {
		if (n > end || n < start) return 0;
		if (start == end) return segTree[index];
		int mid = (start + end) / 2;
		return segTree[index] + get_diff(n, start, mid, index * 2) + get_diff(n, mid + 1, end, index * 2 + 1);
	}
}

namespace gcd {
	ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

	ll segTree[MAX * 4];

	ll update(int pos, ll diff, int index = 1, int start = 1, int end = N) {
		if (pos < start || pos > end) return segTree[index];
		if (pos == start && pos == end) return segTree[index] += diff;
		int mid = (start + end) / 2;

		return segTree[index] = gcd(update(pos, diff, index * 2, start, mid), update(pos, diff, index * 2 + 1, mid + 1, end));
	}

	ll get_gcd(int left, int right, int start = 1, int end = N, int index = 1) {
		if (left > right) return 0;
		if (left == start && end == right) return segTree[index];

		int mid = (start + end) / 2;
		return gcd(get_gcd(left, std::min(mid, right), start, mid, index * 2),
				   get_gcd(std::max(left, mid + 1), right, mid + 1, end, index * 2 + 1));
	}
}

int main() {
	ll t, T, Q, l, r, c, s, i, k;
	std::cin >> T;
	for (t = 1; t <= T; ++t) {
		memset(sum::segTree, 0, sizeof sum::segTree);
		memset(gcd::segTree, 0, sizeof gcd::segTree);

		std::cin >> N >> M;
		std::cin >> A[1]; sum::update_diff(1, 1, A[1]);
		for (i = 2; i <= N; ++i) {
			std::cin >> A[i];
			sum::update_diff(i, i, A[i]);
			gcd::update(i, A[i] - A[i - 1]);
		}
		for (s = 0, k = 1, i = 0; i < M; ++i) {
			std::cin >> Q;
			if (Q == 1) {
				std::cin >> l >> r;
				ll o = sum::get_diff(l);
				if (l == r) s += k * std::abs(o);
				else s += k * std::abs(gcd::gcd(o, gcd::get_gcd(l + 1, r)));
				s %= MOD;
				k++;
			}
			if (Q == 2) {
				std::cin >> l >> r >> c;
				sum::update_diff(l, r, c);
				gcd::update(l, c);
				gcd::update(r + 1, -c);
			}
		}
		std::cout << '#' << t << ' ' << s << '\n';
	}
}