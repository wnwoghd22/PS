#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;

struct Q {
	int k, d;
	bool operator<(const Q& o) const {
		return k == o.k ? d > o.d : k > o.k;
	}
} q[LEN];

int T, N, M, X[LEN], Y[LEN], st[LEN], sp;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) std::cin >> X[i] >> Y[i];
		std::cin >> M;
		for (int i = 0; i < M; ++i) std::cin >> q[i].k >> q[i].d;
		std::sort(q, q + M);

		ld ret = 0;
		ld cur = 0;
		int sp = 0;
		for (int k = N - 1, j = 0; k >= 0; --k) {
			while (j < M && q[j].k == k) {

			}

		}
	}
}