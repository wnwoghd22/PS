#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 100'000;

struct Edge {
	int u, v, w;
	bool operator<(const Edge& r) const { return w > r.w; }
} e[LEN];

int p[10'001];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}
int N, M, A, B;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) std::cin >> e[i].u >> e[i].v >> e[i].w;
	std::cin >> A >> B;
	std::sort(e, e + M);
	memset(p, -1, sizeof p);
	for (int i = 0; i < M; ++i) {
		if (join(e[i].u, e[i].v)) {
			if (find(A) == find(B)) {
				std::cout << e[i].w;
				return 0;
			}
		}
	}
}