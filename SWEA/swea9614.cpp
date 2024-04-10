#include <stdio.h>
#include <string.h>
#define ll long long
#define LEN 100001
int N, K, A[LEN], C, cnt[LEN], l, r;

ll solve() {
	l = r = C = 0;
	memset(cnt, 0, sizeof cnt);
	ll result = 0;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) scanf("%d", A + i);
	while (1) {
		while (r < N && C < K) if (!cnt[A[r++]]++) ++C;
		if (C == K)
			result += N - r + 1;
		if (!--cnt[A[l++]]) {
			if (--C < K && r >= N)
				break;
		}
		if (l >= N) break;
	}
	return result;
}

int main() {
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t)
		printf("#%d %lld\n", t, solve());
}