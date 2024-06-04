#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e4;

struct E {
	int n, c; // num, cap
	bool operator<(const E& o) const { c < o.c; }
} c[LEN], e[LEN];

ll cn[LEN], cs[LEN], en[LEN], es[LEN];

int N, M;

int solve() {
	for (int i = 0; i < N; ++i) std::cin >> c[i].n >> c[i].c;
	for (int i = 0; i < M; ++i) std::cin >> e[i].n >> e[i].c;
	
	// ???
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> N >> M;
		if (!N && !M) break;
		std::cout << solve() << '\n';
	}
}