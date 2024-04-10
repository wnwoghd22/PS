#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;
const ll INF = 1e17;
const int LEN = 101;
const int L = 0;
const int R = 1;

int T, N, a, A;
ll S[LEN], dp[101][101][2];

ll f(int s, int e, int r) {
	if (s == 1 && e == N) return 0;
	ll& ref = dp[s][e][r];
	if (~ref) return ref;
	ref = INF;
	if (e < N) ref = std::min(ref, f(s, e + 1, R) + (N - e + s - 1) * (S[e + 1] - S[r ? e : s]));
	if (s > 1) ref = std::min(ref, f(s - 1, e, L) + (N - e + s - 1) * (S[r ? e : s] - S[s - 1]));
	return ref;
}

int main() {
	std::cin >> T;
	while (T--) {
		memset(dp, -1, sizeof dp);
		std::cin >> N >> a;
		for (int i = 2; i <= N; ++i) {
			std::cin >> A;
			S[i] = S[i - 1] + A;
		}
		std::cout << std::min(f(a, a, L), f(a, a, R)) << '\n';
	}
}