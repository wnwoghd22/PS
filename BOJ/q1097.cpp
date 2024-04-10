#include <iostream>
#include <cstring>

std::string S[8];
int fail[200];
int N, K, visited;

int kmp(std::string p, std::string t) {
	memset(fail, 0, sizeof fail);
	for (int i = 1, j = 0; i < p.length(); ++i) {
		while (j && p[i] != p[j]) j = fail[j - 1];
		if (p[i] == p[j]) fail[i] = ++j;
	}
	int result = 0;
	for (int i = 0, j = 0; i < t.length() - 1; ++i) {
		while (j && t[i] != p[j]) j = fail[j - 1];
		if (t[i] == p[j]) {
			if (j == p.length() - 1) {
				++result;
				j = fail[j];
			}
			else ++j;
		}
	}
	return result;
}

int dfs(int n, std::string s) {
	if (n == N) return kmp(s, s + s) == K;
	int result = 0;
	for (int i = 0; i < N; ++i) {
		if (~visited & 1 << i) {
			visited |= 1 << i;
			result += dfs(n + 1, s + S[i]);
			visited &= ~(1 << i);
		}
	}
	return result;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> S[i];
	std::cin >> K;
	std::cout << dfs(0, "");
}
