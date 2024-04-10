#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
const int LEN = 1e5 + 1;
const int MOD = 1e9 + 7;
char S[LEN];
int N, M;

int main() {
	scanf("%s", S);
	N = strlen(S);
	for (int i = 0, j = 1; i < N; ++i, j = (j << 1) % MOD)
		M = (M + j * (S[i] == 'O')) % MOD;
	printf("%d", M);
}