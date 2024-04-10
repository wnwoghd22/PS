#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'000;

struct E {
	ll X, A;
	bool operator<(const E& r) const { return X < r.X; }
} e[LEN];

int N, X[LEN], A[LEN], ret;
ll D, min, Sr, Sl;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> e[i].X >> e[i].A;
	std::sort(e, e + N);
	for (int i = 1; i < N; ++i) {
		D += (ll)(e[i].X - e[0].X) * e[i].A;
		Sl += e[i].A;
	}
	min = D; Sr = e[0].A;
	for (int i = 1; i < N; ++i) {
		D -= (e[i].X - e[i - 1].X) * Sl;
		D += (e[i].X - e[i - 1].X) * Sr;
		Sl -= e[i].A; Sr += e[i].A;
		if (D < min) {
			min = D;
			ret = i;
		}
	}
	std::cout << e[ret].X;
}