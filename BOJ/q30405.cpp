#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;
int N, M, ans;
ll sum, L, R, S[LEN], Sr, Sl;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, k, p; i < N; ++i) {
		std::cin >> k >> p;
		S[p]++;
		for (int j = 0; j < k - 1; ++j) std::cin >> p;
		S[p]++;
	}
	for (int i = 2; i <= M; ++i) R += S[i] * (i - 1), Sr += S[i];
	ans = 1; sum = R; Sl = S[1];
	for (int i = 2; i <= M; ++i) {
		R -= Sr; Sr -= S[i];
		L += Sl; Sl += S[i];
		if (R + L < sum) {
			sum = R + L;
			ans = i;
		}
	}
	std::cout << ans;
}