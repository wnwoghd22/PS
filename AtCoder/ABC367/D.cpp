#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 1e6 + 1;

int N, M;
int A[LEN * 2];
ll D, S[LEN * 2];
ll cnt[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		A[i + N] = A[i];
	}
	for (int i = 1; i <= 2 * N; ++i) {
		S[i] = A[i] + S[i - 1];
	}

	D = S[N]; // total distance

	ll ret = 0;
	cnt[0]++;
	for (int l = 1, r = 1; l <= N; ++l) {
		for (;;++r) {
			if (S[r] - S[l - 1] >= D) break;
			cnt[S[r] % M]++;
		}
		// std::cout << l << ' ' << r << ' ' << cnt[S[l] % M] << '\n';
		ret += cnt[S[l - 1] % M] - 1;
		cnt[S[l - 1] % M]--;
	}
	std::cout << ret;
}