#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 2e5 + 1;

int N, M;

struct E {
	int A, B;
	int S, T;
} e[LEN];

ll D[LEN];
ll X[LEN];

struct Info {
	int i, j;
	int d;
	bool operator<(const Info& o) const {
		return d != o.d ? d < o.d : j < o.j;
	}
} infos[LEN * 3];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> X[0];
	for (int i = 0; i < M; ++i) {
		std::cin >> e[i].A >> e[i].B >> e[i].S >> e[i].T;
	}
	int len = 0;
	for (int i = 0; i < M; ++i) {
		if (e[i].S >= e[0].T) {
			infos[len++] = { i, 1, e[i].S };
			infos[len++] = { i, -1, e[i].T };
		}
	}
	std::sort(infos, infos + len);

	D[e[0].B] = e[0].T + X[0];
	
	for (int i = 0; i < len; ++i) {
		int k = infos[i].i;
		if (infos[i].j == 1) {
			X[k] = std::max(0ll, D[e[k].A] - e[k].S);
		}
		else {
			D[e[k].B] = std::max(D[e[k].B], e[k].T + X[k]);
		}
	}

	// for (int i = 1; i <= N; ++i) std::cout << D[i] << ' '; std::cout << '\n';

	ll ret = 0;
	for (int i = 1; i < M; ++i)
		std::cout << X[i] << ' ';
}