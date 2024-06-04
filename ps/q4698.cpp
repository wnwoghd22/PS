#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e4 + 1;

struct E {
	int n, c; // num, cap
	bool operator<(const E& o) const { return c < o.c; }
} c[LEN], e[LEN];

ll cn[LEN], cs[LEN], en[LEN], es[LEN];

int N, M;

int solve() {
	for (int i = 0; i < N; ++i) std::cin >> c[i].n >> c[i].c;
	for (int i = 0; i < M; ++i) std::cin >> e[i].n >> e[i].c;
	
	std::sort(c, c + N);
	std::sort(e, e + M);

	for (int i = 0; i < N; ++i) {
		cn[i + 1] = cn[i] + c[i].n;
		cs[i + 1] = cs[i] + (ll)c[i].n * c[i].c;
	}
	for (int i = 0; i < M; ++i) {
		en[i + 1] = en[i] + e[i].n;
		es[i + 1] = es[i] + (ll)e[i].n * e[i].c;
	}
	ll min_cut = std::min(es[M], cs[N]);
	ll S = es[M];
	ll E = 0;
	ll X = std::min((ll)c[N - 1].c, en[M]);
	ll y = cn[N];
	for (int x = 1, i = M - 1, j = 0; x <= X; ++x) {
		if (e[i].n == 0) --i;
		S -= e[i].c; e[i].n--;

		while (j < N && c[j].c <= x) {
			y -= c[j].n;
			E += (ll)c[j].n * c[j].c;
			++j;
		}

		ll cur = S + E + x * y;
		if (cur < min_cut)
			min_cut = cur;
	}
	return min_cut >= cs[N];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> N >> M;
		if (!N && !M) break;
		std::cout << solve() << '\n';
	}
}