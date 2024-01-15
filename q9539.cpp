#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#include <cassert>

typedef long long ll;
const int LEN = 2e5 + 1;
const ll INF = 1e17;

std::vector<int> graph[LEN];
int T, N, t, w[LEN];

struct E {
	ll c, w;
	int i;
	bool operator<(const E& r) const { return c == r.c ? w < r.w : c > r.c; }
};

std::priority_queue<E> pq[LEN];
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	// std::cout << "merge " << a << ' ' << b << '\n';
	a = find(a); b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}
int pqi[LEN];
int merge(int a, int b) {
	if (pq[a].size() > pq[b].size()) {
		while (pq[b].size()) {
			pq[a].push(pq[b].top());
			pq[b].pop();
		}
		pqi[b] = a;
		return a;
	}
	while (pq[a].size()) {
		pq[b].push(pq[a].top());
		pq[a].pop();
	}
	return b;
}

int dfs(int u, int p = 0) {
	int idx = u;
	if (u == t) {
		pq[u].push({ -std::min(w[u], 0), INF, u });
		return u;
	}
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int c = dfs(v, u);
		idx = merge(idx, c);
	}
	ll cost = 0, weight = 0;
	if (w[u] > 0) weight = w[u];
	else cost = -w[u];
	while (pq[idx].size() && (cost >= weight || pq[idx].top().c <= cost)) {
		if (pq[idx].top().c <= weight)
			weight += pq[idx].top().w - pq[idx].top().c;
		else {
			cost += pq[idx].top().c - weight;
			weight = pq[idx].top().w;
		}
		join(u, pq[idx].top().i);
		pq[idx].pop();
	}
	if (weight > cost) pq[idx].push({ cost, weight, u });
	return idx;
}

void solve() {
	std::cin >> N >> t;
	memset(p, -1, sizeof p);
	for (int i = 1; i <= N; ++i) std::cin >> w[i];
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int idx = dfs(1);
	ll cost = 0, weight = 0;
	while (pq[idx].size()) {
		assert(pq[idx].top().w > pq[idx].top().c);
		if (pq[idx].top().c <= weight) {
			weight += pq[idx].top().w - pq[idx].top().c;
			join(1, pq[idx].top().i);
			pq[idx].pop();
		}
		else break;
	}
	std::cout << (find(1) == find(t) ? "escaped\n" : "trapped\n");
	for (int i = 1; i <= N; ++i) graph[i].clear();
	while (pq[idx].size()) pq[idx].pop();
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) solve();
}