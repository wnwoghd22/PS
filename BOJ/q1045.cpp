#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

const int LEN = 50;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

struct E { 
	int u, v;
	bool operator<(const E& r) const {
		return u == r.u ? v < r.v : u < r.u;
	}
} e[LEN * LEN];
int N, M, len, mst;

char g[LEN][LEN + 1];
int cnt[50];
std::vector<E> aux;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> g[i];
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (g[i][j] == 'Y')
				e[len++] = { i, j };
		}
	}
	memset(p, -1, sizeof p);
	for (int i = 0; i < len; ++i) {
		if (join(e[i].u, e[i].v)) {
			++cnt[e[i].u];
			++cnt[e[i].v];
			++mst;
		}
		else aux.push_back(e[i]);
	}
	if (mst < N - 1) std::cout << -1;
	else if (len < M) std::cout << -1;
	else {
		// std::sort(aux.begin(), aux.end());
		for (int i = 0; i < M - N + 1; ++i) {
			++cnt[aux[i].u];
			++cnt[aux[i].v];
		}
		for (int i = 0; i < N; ++i) std::cout << cnt[i] << ' ';
	}
}
