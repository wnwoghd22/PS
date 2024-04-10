#include <iostream>

typedef long long ll;
const int LEN = 100'001;
ll N, Q, A, B, T, seg_sum[LEN * 4], seg_gcd[LEN * 4];
void update_sum(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) { seg_sum[i] += d; return; }
	int m = s + e >> 1;
	update_sum(l, r, d, s, m, i << 1), update_sum(l, r, d, m + 1, e, i << 1 | 1);
}
ll get_sum(int x, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return 0;
	if (s == e) return seg_sum[i];
	int m = s + e >> 1;
	return seg_sum[i] + get_sum(x, s, m, i << 1) + get_sum(x, m + 1, e, i << 1 | 1);
}

ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
void update_gcd(int x, ll d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { seg_gcd[i] += d; return; }
	int m = s + e >> 1;
	update_gcd(x, d, s, m, i << 1), update_gcd(x, d, m + 1, e, i << 1 | 1);
	seg_gcd[i] = gcd(std::abs(seg_gcd[i << 1]), std::abs(seg_gcd[i << 1 | 1]));
}
ll get_gcd(int l, int r, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return std::abs(seg_gcd[i]);
	int m = s + e >> 1;
	return gcd(get_gcd(l, r, s, m, i << 1), get_gcd(l, r, m + 1, e, i << 1 | 1));
}

int main() {
	std::cin >> N;
	for (ll i = 1, A0 = 0, A1; i <= N; ++i, A0 = A1) {
		std::cin >> A1;
		update_sum(i, i, A1);
		update_gcd(i, A1 - A0);
	}
	std::cin >> Q;
	while (Q--) {
		std::cin >> T >> A >> B;
		if (T) {
			update_sum(A, B, T);
			update_gcd(A, T);
			update_gcd(B + 1, -T);
		}
		else std::cout << gcd(get_sum(A), get_gcd(A + 1, B)) << '\n';
	}
}