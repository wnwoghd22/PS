#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int ACINT = 532741;
int N, K;
int w[50];
char s[16];

int dfs(int bit, int i, int n) {
	int result = 0;
	if (n == K) {
		for (int j = 0; j < N; ++j)
			result += (bit | w[j]) == bit;
	}
	else {
		for (int j = i; j < 26; ++j) {
			if ((1 << j) & ACINT) continue;
			result = std::max(result, dfs(bit | 1 << j, j + 1, n + 1));
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	if (K < 5) std::cout << 0;
	else {
		for (int i = 0; i < N; ++i) {
			std::cin >> s;
			for (int j = 0; s[j]; ++j)
				w[i] |= 1 << (s[j] - 'a');
		}
		std::cout << dfs(ACINT, 0, 5);
	}
}