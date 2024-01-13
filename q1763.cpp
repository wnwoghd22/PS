#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 1001;

int N, R;
int C[LEN];
int F[LEN], par[LEN];
bool visited[LEN];

int find(int i) { return F[i] < 0 ? i : F[i] = find(F[i]); }
int join(int u, int p) {
	u = find(u), p = find(p);
	if (u == p) return 0;
	C[p] += C[u];
	F[p] += F[u];
	F[u] = p;
	return 1;
}
int get_max() {
	int u = -1;
	ll num = 0, den = 1;
	for (int i = 1; i <= N; ++i) {
		if (i == R || visited[i]) continue;
		if (num * -F[i] <= den * C[i]) {
			u = i;
			num = C[i];
			den = -F[i];
		}
	}
	return u;
}

int main() {
	std::cin >> N >> R;
	for (int i = 1; i <= N; ++i) std::cin >> C[i];
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		par[v] = u;
	}
	ll cost = 0;
	memset(F, -1, sizeof F);
	for (int i = 1, u, p; i < N; ++i) {
		u = get_max();
		// std::cout << u << '\n';
		visited[u] = 1;
		p = find(par[u]);
		cost += C[u] * -F[p];
		join(u, p);
	}
	std::cout << cost + C[R];
}