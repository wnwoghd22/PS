#include <iostream>
#include <cstring>

const int MOD = 1e6;
const int LEN = 5e4 + 1;

char S[LEN];
int len, dp[LEN] = { 1, };
int ctoi(char d1, char d2) { return (d1 - '0') * 10 + d2 - '0'; }
bool valid(int i) { return 10 <= i && i <= 26; }

int main() {
	std::cin >> S;
	len = strlen(S);

	dp[1] = S[0] != '0';
	for (int i = 2; i <= len; ++i) {
		dp[i] += (S[i - 1] != '0') * dp[i - 1];
		dp[i] += valid(ctoi(S[i - 2], S[i - 1])) * dp[i - 2];
		dp[i] %= MOD;
	}
	std::cout << dp[len];
}