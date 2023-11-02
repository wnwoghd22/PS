#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 300'001;
const ll MOD = 1e9 + 7;
int K, N, A[LEN], rank = 1, ans[LEN], f[LEN];

struct Fenwick {
	int t[LEN];
	ll sum(int i) {
		ll result = 0;
		while (i > 0) {
			result = (result + t[i]) % MOD;
			i -= i & -i;
		}
		return result;
	}
	void update(int i, ll d) {
		while (i <= K) {
			t[i] = (t[i] + d) % MOD;
			i += i & -i;
		}
	}
} cnt, sum;

int L[LEN], R[LEN];
struct Query { 
	int t, i;
	bool operator<(const Query& r) const { return t < r.t; }
} q[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> K >> N;
	for (ll i = f[0] = 1; i <= K; ++i) f[i] = i * f[i - 1] % MOD; // preprocess
	for (int i = 0; i < K; ++i) std::cin >> A[K - i];
	for (int i = 0; i < N; ++i) {
		std::cin >> L[i] >> R[i];
		L[i] = K - L[i] + 1; R[i] = K - R[i] + 1;
		q[i << 1] = { L[i], i }; q[i << 1 | 1] = { R[i], i };
	}
	std::sort(q, q + N * 2);
	for (int k = 1, i = 0, j, l, r, max, min, eff; k <= K; ++k) {
		while (i < N * 2 && q[i].t == k) {
			j = q[i].i;
			l = A[L[j]], r = A[R[j]]; max = std::max(l, r), min = std::min(l, r);
			eff = (q[i].t == R[j] ? 1 : -1) * (l > r ? 1 : -1);

			ans[j] = (ans[j] + eff * f[k - 1] * (cnt.sum(max - 1) - cnt.sum(min) + (q[i].t == L[j])) + MOD * MOD) % MOD;
			ans[j] = (ans[j] + eff * (sum.sum(max - 1) - sum.sum(min)) + MOD * MOD) % MOD;

			++i;
		}
		rank = (rank + f[k - 1] * cnt.sum(A[k] - 1)) % MOD;
		cnt.update(A[k], 1); sum.update(A[k], f[k - 1]);
	}
	for (int i = 0; i < N; ++i) std::cout << (rank + ans[i] + MOD) % MOD << '\n';
}