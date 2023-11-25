#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int MOD = 10007;
const int LEN = 100'001;
int dp[LEN << 1];

int solution(int n, vector<int> tops) {
	dp[0] = dp[1] = 1;
	for (int i = 2; i <= n * 2 + 1; ++i) {
		dp[i] = (dp[i - 2] + dp[i - 1] * (1 + (i & 1) * tops[(i >> 1) - 1])) % MOD;
		if (i & 1) dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
		else dp[i] = (dp[i - 1] + dp[i - 2] * (2 + tops[(i >> 1) - 1])) % MOD;
		
	}
	return dp[n * 2 + 1];
}
