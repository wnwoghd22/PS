#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>

const int NUM = 500;
const int P_LEN = 10'001;
const int LEN = 100'001;

int N, L, l[NUM], fail[P_LEN], cache[LEN];
char t[LEN], p[P_LEN], dp[NUM][LEN];

int f(int i) {
	if (i == L) return 0;
	int& ref = cache[i];
	if (~ref) return ref;
	ref = f(i + 1);
	for (int j = 0; j < N; ++j) {
		if (dp[j][i])
			ref = std::max(ref, l[j] + f(i + l[j]));
	}
	return ref;
}

int main() {
	scanf("%s %d", t, &N);
	L = strlen(t);
	for (int n = 0; n < N; ++n) {
		scanf("%s", p);
		l[n] = strlen(p);
		memset(fail, 0, sizeof fail);
		for (int i = 1, j = 0; p[i]; ++i) {
			while (j && p[j] ^ p[i]) j = fail[j - 1];
			if (p[j] == p[i]) fail[i] = ++j;
		}
		for (int i = 0, j = 0; t[i]; ++i) {
			while (j && p[j] ^ t[i]) j = fail[j - 1];
			if (t[i] == p[j]) {
				if (j == l[n] - 1) {
					dp[n][i - j] = 1;
					j = fail[j];
				}
				else ++j;
			}
		}
	}
	memset(cache, -1, sizeof cache);
	printf("%d", f(0));
}