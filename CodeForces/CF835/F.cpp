#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int LEN = 2e5;
const int INF = 1e9;

ll A[LEN], S[LEN];
ll N, C, D;

ll get_coin(int k) {
	if (k < 0) return 0;
	if (k < N) return S[k];
	else return S[N - 1];
}

int binary_search() {
	int l = 0, r = INF, mid, result = -1;

	while (l <= r) {
		mid = (l + r) / 2;
		ll c = get_coin(mid) * (D / (mid + 1ll)) + get_coin(D % (mid + 1ll) - 1);

		if (c >= C) {
			result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return result;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(A, 0, sizeof A);
		memset(S, 0, sizeof S);

		std::cin >> N >> C >> D;
		for (int i = 0; i < N; ++i) std::cin >> A[i];
		std::sort(A, A + N, std::greater<>()); S[0] = A[0];
		for (int i = 1; i < N; ++i) S[i] = A[i] + S[i - 1];

		ll result = binary_search();

		if (result > D) std::cout << "Infinity\n";
		else if (result == -1) std::cout << "Impossible\n";
		else std::cout << result << '\n';
	}
}