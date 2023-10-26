#include <iostream>
#include <cstring>
#include <algorithm>

const int INF = 1e9;
const int LEN = 301;
const int L = 0;
const int R = 1;

int N, M, A, a;
int S[LEN], dp[LEN][LEN][2];

int f(int s, int e, int r, int i) {
	if (!i) return 0;
	int& ref = dp[s][e][r];
	if (~ref) return ref;
	ref = INF;
	if (e < N - 1) ref = std::min(ref, f(s, e + 1, R, i - 1) + i * (S[e + 1] - S[r ? e : s]));
	if (s > 0) ref = std::min(ref, f(s - 1, e, L, i - 1) + i * (S[r ? e : s] - S[s - 1]));
	return ref;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		if (!S[i]) A = 1;
	}
	if (!A) ++N;
	std::sort(S, S + N); 
	for (int i = 0; i < N; ++i) {
		if (!S[i]) {
			a = i;
			break;
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		memset(dp, -1, sizeof dp);
		ans = std::max(ans, M * i - std::min(f(a, a, L, i), f(a, a, R, i)));
	}
	std::cout << ans + M * A << '\n';
}