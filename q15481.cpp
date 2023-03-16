#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int LEN = 200'001;

int N, M, p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

struct Info {
	int u, v, i;
	ll w;
	bool is_spanning;
	bool operator<(const Info& r) const { return w > r.w; }
} edges[LEN];
struct Edge { int v; ll w; };

std::vector<Edge> graph[LEN];
ll kruskal() {
	std::priority_queue<Info> pq;
	memset(p, -1, sizeof p);
	int m = N - 1;
	ll mst = 0;
	for (int i = 0; i < M; ++i) pq.push(edges[i]);

	while (m) {
		Info e = pq.top(); pq.pop();
		if (join(e.u, e.v)) {
			edges[e.i].is_spanning = true;
			mst += e.w;
			graph[e.u].push_back({ e.v, e.w });
			graph[e.v].push_back({ e.u, e.w });
			--m;
		}
	}
	return mst;
}

int level[LEN], parent[LEN][18];
ll max_w[LEN][18];

void dfs(int u, ll w, int p = 0) {
	level[u] = level[p] + 1;
	parent[u][0] = p;
	max_w[u][0] = w;
	for (int i = 1, v = p; v; v = parent[u][i++]) {
		parent[u][i] = parent[v][i - 1];
		max_w[u][i] = std::max(max_w[u][i - 1], max_w[v][i - 1]);
	}
	for (const Edge& e : graph[u]) {
		if (e.v == p) continue;
		dfs(e.v, e.w, u);
	}
}

ll lca_max_weight(int u, int v) {
	ll w = 0;
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = 17; i >= 0; --i) {
			if (level[parent[v][i]] >= level[u]) {
				w = std::max(w, max_w[v][i]);
				v = parent[v][i];
			}
		}
	}
	if (u == v) return w;

	for (int i = 17; i >= 0; --i) {
		if (parent[u][i] ^ parent[v][i]) {
			w = std::max({ w, max_w[u][i], max_w[v][i] });
			u = parent[u][i];
			v = parent[v][i];
		}
	}

	return std::max({ w, max_w[u][0], max_w[v][0] });
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
		edges[i].i = i; edges[i].is_spanning = false;
	}

	ll sum = kruskal();
	dfs(1, 0, 0);

	for (int i = 0; i < M; ++i) {
		if (edges[i].is_spanning) std::cout << sum << '\n';
		else std::cout << sum + edges[i].w - lca_max_weight(edges[i].u, edges[i].v) << '\n';
	}
}