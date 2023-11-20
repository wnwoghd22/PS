#include <iostream>
#include <algorithm>

const int LEN = 100'001;

int L[LEN], D[LEN];
int ord[2][LEN];
int incoming[2][LEN];
int A[LEN];

int order;
void dfs0(int u) {
	ord[0][u] = ++order;
	if (!--incoming[0][D[u]]) dfs0(D[u]);
	if (!--incoming[0][L[u]]) dfs0(L[u]);
}
void dfs1(int u) {
	ord[1][u] = ++order;
	if (!--incoming[1][L[u]]) dfs1(L[u]);
	if (!--incoming[1][D[u]]) dfs1(D[u]);
}

struct Pos { int x, y; } p[LEN];

int N, M, K;

int main() {
	std::cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) std::cin >> p[i].x >> p[i].y;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		if (p[u].x == p[v].x) {
			if (p[u].y < p[v].y) {
				D[v] = u;
				incoming[0][u]++;
				incoming[1][u]++;
			}
			else {
				D[u] = v;
				incoming[0][v]++;
				incoming[1][v]++;
			}
		}
		else {
			if (p[u].x < p[v].x) {
				L[u] = v;
				incoming[0][v]++;
				incoming[1][v]++;
			}
			else {
				L[v] = u;
				incoming[0][u]++;
				incoming[1][u]++;
			}
		}
	}

	for (int i = 0; i < N; ++i) A[i] = i + 1;

	std::sort(A, A + N, [](int a, int b) { return p[a].y == p[b].y ? p[a].x < p[b].x : p[a].y < p[b].y; });
	for (int i = 0; i < N; ++i)
		if (!ord[0][A[i]] && !incoming[0][A[i]])
			dfs0(A[i]);

	std::sort(A, A + N, [](int a, int b) { return p[a].x == p[a].x ? p[a].y > p[b].y : p[a].x > p[b].x; });
	for (int i = 0; i < N; ++i)
		if (!ord[1][A[i]] && !incoming[1][A[i]])
			dfs1(A[i]);

	for (int i = 1; i <= N; ++i) std::cout << ord[0][i] << ' '; std::cout << '\n';
	for (int i = 1; i <= N; ++i) std::cout << ord[1][i] << ' '; std::cout << '\n';

	for (int i = 0, a, b; i < K; ++i) {
		std::cin >> a >> b;
		if (p[a].x > p[b].x) std::swap(a, b);
		std::cout << (ord[0][a] < ord[0][b] && ord[1][a] < ord[1][b] ? "TAK\n" : "NIE\n");
	}
}