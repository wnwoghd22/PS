#include <iostream>
#include <cstring>

char S[51];
char T[50][51];
int N, M, l[50], dp[51], cnt[26];

int main() {
	std::cin >> S;
	M = strlen(S);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> T[i];
		l[i] = strlen(T[i]);
	}
	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	for (int i = 1, cost; i <= M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i < l[j]) continue;
			if (!~dp[i - l[j]]) continue;
			memset(cnt, 0, sizeof cnt);
			cost = 0;
			for (int k = 0; k < l[j]; ++k) {
				cnt[S[i - l[j] + k] - 'a']++;
				cnt[T[j][k] - 'a']--;
				if (S[i - l[j] + k] ^ T[j][k]) ++cost;
			}
			for (int k = 0; k < 26; ++k) if (cnt[k]) {
				cost = -1; break;
			}
			if (~cost) {
				if (!~dp[i]) dp[i] = 1e9;
				dp[i] = std::min(dp[i], dp[i - l[j]] + cost);
			}
		}
	}
	std::cout << dp[M];
}