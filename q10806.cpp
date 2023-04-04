#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

const int LEN = 100'001;
struct Edge {
	int u, v;
	bool operator<(const Edge& r) const {
		return u == r.u ? v < r.v : u < r.u;
	}
} edges[LEN << 1];

int p[LEN]; // union-find
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}
int V, E;
int order[LEN]; // euler tour order

std::vector<Edge> graph[LEN];
std::vector<int> articulation_edge;

std::stack<int> stack;
int dfs(int u, int p = 0) {
	int min = order[u] = order[p] + 1;
	// std::cout << u << ' ' << p << ' ' << min << '\n';
	stack.push(u);
	for (const Edge& e : graph[u]) {
		int v = e.v, i = e.u; // index of edge
		// std::cout << v << '\n';
		if (v == p) continue;
		if (!order[v]) {
			int next = dfs(v, u);
			if (next > order[u]) // articulation edge
				articulation_edge.push_back(i);
			min = std::min(min, next);
		}
		else min = std::min(min, order[v]);
	}
	if (min == order[u]) { // cycle -> BCC found
		// std::cout << "cycle: " << u << ' ' << min << ' ' << order[u] << '\n';
		int top = stack.top(); stack.pop();
		while (top != u) {
			join(top, stack.top());
			top = stack.top(); stack.pop();
		}
	}
	return min;
}

int leaf[LEN];
std::vector<int> leaf_set[LEN];
int dfs_leaf(int u, int p = 0) {
	if (graph[u].size() == 1 && graph[u][0].v == p) return leaf[u] = 1;
	for (const Edge& e : graph[u]) {
		int v = e.v;
		if (v == p) continue;
		leaf[u] += dfs_leaf(v, u);
	}
	// std::cout << "leaves count " << u << ' ' << leaf[u] << '\n';
	return leaf[u];
}
int get_centroid(int u, int p, int s) { // leaf centroid
	for (const Edge& e : graph[u]) {
		if (e.v != p && leaf[e.v] * 2 > s)
			return get_centroid(e.v, u, s);
	}
	return u;
}
std::priority_queue<Edge> pq;
void push_leaves(int u, int p, int i) {
	// std::cout << "check leaf " << u << ' ' << p << '\n';
	if (graph[u].size() == 1 && graph[u][0].v == p) {
		// std::cout << "push leaf " << u << " at " << i << '\n';
		return leaf_set[i].push_back(u);
	}
	for (const Edge& e : graph[u]) {
		int v = e.v;
		if (v == p) continue;
		push_leaves(v, u, i);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	memset(p, -1, sizeof p);
	std::cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		std::cin >> edges[i].u >> edges[i].v;
		if (edges[i].u > edges[i].v)
			std::swap(edges[i].u, edges[i].v);
	}
	std::sort(edges, edges + E);
	for (int i = 0, u, v; i < E; ++i) {
		u = edges[i].u, v = edges[i].v;
		graph[u].push_back({ i, v });
		graph[v].push_back({ i, u });
	}
	dfs(1);
	for (int i = 0; i < E - 1; ++i) {
		if (edges[i].u == edges[i + 1].u && edges[i].v == edges[i + 1].v)
			join(edges[i].u, edges[i].v);
	}

	// make tree
	for (std::vector<Edge>& vert : graph) vert.clear();
	for (int i = 0, u, v; i < (int)articulation_edge.size(); ++i) {
		// std::cout << edges[articulation_edge[i]].u << ' ' << edges[articulation_edge[i]].v << '\n';
		u = find(edges[articulation_edge[i]].u);
		v = find(edges[articulation_edge[i]].v);
		if (u != v) {
			graph[u].push_back({ i, v });
			graph[v].push_back({ i, u });
		}
	}
	dfs_leaf(find(1));
	int c = get_centroid(find(1), 0, leaf[find(1)]);
	for (const Edge& e : graph[c]) {
		// std::cout << "check vertex " << e.v << '\n';
		push_leaves(e.v, c, e.v);
		pq.push({ (int)leaf_set[e.v].size(), e.v });
	}
	// std::cout << c << '\n';
	std::cout << (leaf[find(1)] + 1 >> 1) << '\n'; // num of bridge
	while (pq.size() > 1) {
		Edge s1 = pq.top(); pq.pop();
		Edge s2 = pq.top(); pq.pop();
		std::cout << leaf_set[s1.v].back() << ' ' << leaf_set[s2.v].back() << '\n';
		leaf_set[s1.v].pop_back();
		leaf_set[s2.v].pop_back();
		if (leaf_set[s1.v].size()) pq.push({ (int)leaf_set[s1.v].size(), s1.v });
		if (leaf_set[s2.v].size()) pq.push({ (int)leaf_set[s2.v].size(), s2.v });
	}
	if (pq.size()) {
		Edge s = pq.top();
		for (const int& v : leaf_set[s.v]) {
			std::cout << c << ' ' << v << '\n';
		}
	}
}