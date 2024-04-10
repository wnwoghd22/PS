#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>

int N, A[26];
char S[9];

int main() {
	scanf("%d", &N);
	for (int i = 0, l; i < N; ++i) {
		scanf("%s", S);
		l = strlen(S);
		for (int j = l - 1, d = 1; j >= 0; --j, d *= 10) {
			A[S[j] - 'A'] += d;
		}
	}
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 25 - i; ++j) {
			if (A[j] < A[j + 1]) {
				int tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = tmp;
			}
		}
	}
	int ret = 0;
	for (int i = 0; i < 10; ++i) ret += A[i] * (9 - i);
	printf("%d", ret);
}