#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 5e4 + 1;
const ll INF = 1e17;

int N, K;
ll S[LEN], dp[LEN];

ll f(int j, int i) { return dp[j] - j * S[i] - i * S[j] + j * S[j]; }

ll cross(int a, int b) {
	int l = 1, r = N, m, x = r + 1;
	while (l <= r) {
		m = l + r >> 1;
		ll ya = f(a, m);
		ll yb = f(b, m);
		if (yb <= ya) {
			x = std::min(x, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return x;
}

int dq[LEN], x[LEN], head, tail, cnt[LEN];

int check(ll lambda) {
	head = tail = 0;
	for (int i = 1, X; i <= N; ++i) {
		while (head > tail && x[tail + 1] <= i) ++tail;
		dp[i] = f(dq[tail], i) + i * S[i] + lambda;
		cnt[i] = cnt[dq[tail]] + 1;
		while (head > tail && x[head] >= cross(dq[head], i)) --head;
		dq[++head] = i;
		x[head] = cross(dq[head - 1], i);
	}
	std::cout << "lambda: " << lambda << '\n';
	for (int i = 1; i <= N; ++i) std::cout << dp[i] << ' ';
	std::cout << "cnt: " << cnt[N] << '\n';
	return cnt[N];
}

ll solve() {
	ll l = 0, r = S[N] * N + 1, m, ret = S[N] * N + 1, c;
	while (l <= r) {
		m = l + r >> 1;
		if ((c = check(m)) <= K) {
			ret = std::min(ret, dp[N] - m * c);
			r = m - 1;
		}
		else l = m + 1;
	}
	return ret;
}

int main() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		std::cin >> S[i];
		S[i] += S[i - 1];
	}
	std::cout << solve();
}