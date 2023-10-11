#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 2e5 + 1;
const int INF = 2e9 + 7;

ll dp[LEN], S[LEN];
int N[2], idx[2], C = LEN >> 1, A[2][(LEN >> 1) + 2];

int cnt[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	memset(cnt, -1, sizeof cnt);
	std::cin >> N[0] >> N[1];
	A[0][0] = -INF; for (int i = 1; i <= N[0]; ++i) std::cin >> A[0][i]; A[0][N[0] + 1] = INF;
	A[1][0] = -INF; for (int i = 1; i <= N[1]; ++i) std::cin >> A[1][i]; A[1][N[1] + 1] = INF;
	cnt[C] = 0;
	idx[0] = idx[1] = 1;

	for (int i = 1, j, k; i <= N[0] + N[1]; ++i) {
		if (idx[0] <= N[0] && idx[1] <= N[1]) k = A[0][idx[0]] > A[1][idx[1]];
		else k = idx[1] <= N[1];

		j = cnt[C += -1 + k * 2];
		S[i] = S[i - 1] + A[k][idx[k]] * (-1 + k * 2);
		
		dp[i] = k ? INF : dp[i - 1];
		if (~j) dp[i] = std::min(dp[i], dp[j] + std::abs(S[i] - S[j]));
		
		cnt[C] = i;
		if (idx[k] <= N[k]) ++idx[k];
	}
	std::cout << dp[N[0] + N[1]];
}