#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;
const ll INF = 1e17;
const int LEN = 301;
const int L = 0;
const int R = 1;

int N, M, A, a;
ll S[LEN], dp[LEN][LEN][2];

ll f(int s, int e, int r) {
	if (s == 1 && e == N) return 0;
	ll& ref = dp[s][e][r];
	if (~ref) return ref;
	ref = 0;
	// if (e < N) ref = std::max(ref, f(s, e + 1, R) + (N - e + s - 1) * (S[e + 1] - S[r ? e : s]));
	// if (s > 1) ref = std::max(ref, f(s - 1, e, L) + (N - e + s - 1) * (S[r ? e : s] - S[s - 1]));
	return ref;
}

int main() {
	memset(dp, -1, sizeof dp);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		if (!S[i]) A = 1;
	}
	if (A) ++N;
	std::sort(S, S + N); 
	for (int i = 0; i < N; ++i) {
		if (!S[i]) {
			a = i;
			break;
		}
	}

	std::cout << std::max(f(a, a, L), f(a, a, R)) + M * A << '\n';
}