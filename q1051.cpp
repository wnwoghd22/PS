#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

char S[50][51];
int N, M, L;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) scanf("%s", S[i]);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int l = L; i + l < N && j + l < M; ++l) {
				if (S[i][j] == S[i + l][j] && S[i][j] == S[i][j + l] && S[i][j] == S[i + l][j + l]) {
					L = l;
				}
			}
		}
	}
	printf("%d", (L + 1) * (L + 1));
}