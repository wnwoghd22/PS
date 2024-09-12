#include <iostream>
#include <cstring>

const int LEN = 10'001;

const char* MORSE[] = {
	".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
	"..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
	"--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
	"-.--", "--.."
};

int D, N, len, idx;
char S[LEN], T[30];
int trie[LEN * 80][2];
int dp[LEN];
int O[LEN * 80];

int solve() {
	memset(trie, -1, sizeof trie);
	memset(O, 0, sizeof O);
	memset(dp, 0, sizeof dp);
	idx = 0;
	std::cin >> S >> N;
	len = strlen(S);

	for (int i = 0, cur; i < N; ++i) {
		std::cin >> T;
		cur = 0;
		for (int j = strlen(T) - 1; j >= 0; --j) {
			const char* c = MORSE[T[j] - 'A'];
			for (int k = strlen(c) - 1; k >= 0; --k) {
				int x = c[k] == '.' ? 0 : 1;
				if (!~trie[cur][x]) trie[cur][x] = ++idx;
				cur = trie[cur][x];
			}
		}
		++O[cur];
	}
	dp[0] = 1;
	for (int i = 0, cur; i < len; ++i) {
		cur = 0;
		for (int j = i; j >= 0; --j) {
			int x = S[j] == '.' ? 0 : 1;
			if (!~trie[cur][x]) break;
			cur = trie[cur][x];
			dp[i + 1] += dp[j] * O[cur];
		}
	}
	return dp[len];
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> D;
	while (D--) std::cout << solve() << '\n';
}