#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

const int LEN = 100'001;
struct Edge { int u, v; } edges[LEN];
std::vector<std::vector<int>> SCC;
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
int ord, order[LEN]; // euler tour order

std::vector<Edge> graph[LEN];
bool lucky[LEN];

std::stack<int> stack;
int dfs(int u, int p = 0) {
	int min = order[u] = ++ord;
	for (const Edge& e : graph[u]) {
		int v = e.v, i = e.u; // index of edge
		if (v == p) continue;
		if (order[u] > order[v]) stack.push(i); // new edge
		if (!order[v]) { // tree edge
			int next = dfs(v, u);
			if (next >= min) { // min order of subtree is bigger -> BCC found
				int top = stack.top();
				std::vector<int> scc;
				while (stack.size()) {
					int cur = stack.top(); stack.pop();
					scc.push_back(cur);
					join(top, cur);
					if (cur == i) break;
					top = cur;
				}
				SCC.push_back(scc);
			}
			min = std::min(min, next);
		}
		else min = std::min(min, order[v]);
	}
	return min;
}

int visited[LEN]; // visited array for bfs

int bfs(int i) {
	int result = 0;
	const std::vector<int>& scc = SCC[i];
	int group = find(scc[0]);
	std::queue<int> q;
	int s = edges[scc[0]].u;
	q.push(s);
	visited[s] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (const Edge& e : graph[u]) {
			int v = e.v, i = e.u;
			if (find(i) != group) continue; // not in scc group
			if (visited[v]) {
				if (visited[u] == visited[v]) { // odd cycle found
					result = 1;
					break;
				}
			}
			else {
				visited[v] = visited[u] + 1;
				q.push(v);
			}
		}
		if (result) break;
	}
	for (const int& i : scc) visited[edges[i].u] = visited[edges[i].v] = 0;

	return result;
}

void bfs_mask(int i) {
	const std::vector<int>& scc = SCC[i];
	int group = find(scc[0]);
	std::queue<int> q;
	int s = edges[scc[0]].u;
	q.push(s);
	visited[s] = lucky[s] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (const Edge& e : graph[u]) {
			int v = e.v, i = e.u;
			if (find(i) != group) continue; // not in scc group
			if (!visited[v]) {
				visited[v] = lucky[v] = 1;
				q.push(v);
			}
		}
	}
	for (const int& i : scc) visited[edges[i].u] = visited[edges[i].v] = 0;
}

int solve() {
	SCC.clear();
	memset(p, -1, sizeof p);
	for (std::vector<Edge>& v : graph) v.clear();
	memset(order, 0, sizeof order);
	memset(lucky, 0, sizeof lucky);
	ord = 0;

	std::cin >> V >> E;
	for (int i = 0, a, b; i < E; ++i) {
		std::cin >> a >> b;
		edges[i].u = a;
		edges[i].v = b;
		graph[a].push_back({ i, b });
		graph[b].push_back({ i, a });
	}
	dfs(1);

	for (int i = 0; i < SCC.size(); ++i) {
		std::cout << "SCC " << i << '\n';
		for (const int& e : SCC[i]) {
			std::cout << edges[e].u << ' ' << edges[e].v << '\n';
		}
		if (bfs(i))
			bfs_mask(i);
	}
	int count = 0;
	for (int i = 1; i <= V; ++i)
		if (lucky[i])
			++count;
	return count;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}