#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

const int LEN = 100'001;
struct Edge { int u, v; } edges[LEN];
int p[LEN]; // union-find
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}
int bcc_count, bcc_index[LEN], bcc_stack[LEN + 1], bcc[LEN];

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
			if (next >= order[u]) { // min order of subtree is bigger -> BCC found
				int top = stack.top();
				bcc_index[i] = bcc_count;
				int bcc_i = bcc_stack[bcc_count++];
				while (stack.size()) {
					int cur = stack.top(); stack.pop();
					bcc[bcc_i++] = cur;
					join(top, cur);
					if (cur == i) break;
					top = cur;
				}
				bcc_stack[bcc_count] = bcc_i;
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
	int group = find(bcc[bcc_stack[i]]);
	std::queue<int> q;
	int s = edges[bcc[bcc_stack[i]]].u;
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
	for (int k = bcc_stack[i]; k < bcc_stack[i + 1]; ++k) {
		int e = bcc[k];
		visited[edges[e].u] = visited[edges[e].v] = 0;
	}
	return result;
}

int solve() {
	memset(p, -1, sizeof p);
	for (std::vector<Edge>& v : graph) v.clear();
	memset(order, 0, sizeof order);
	memset(lucky, 0, sizeof lucky);
	ord = bcc_count = bcc_stack[0] = 0;

	std::cin >> V >> E;
	for (int i = 0, a, b; i < E; ++i) {
		std::cin >> a >> b;
		edges[i].u = a;
		edges[i].v = b;
		graph[a].push_back({ i, b });
		graph[b].push_back({ i, a });
	}
	for (int u = 1; u <= V; ++u) {
		if (!order[u])
			dfs(u);
	}

	for (int i = 0; i < bcc_count; ++i) {
		if (bfs(i)) {
			for (int k = bcc_stack[i]; k < bcc_stack[i + 1]; ++k) {
				int e = bcc[k];
				lucky[edges[e].u] = lucky[edges[e].v] = 1;
			}
		}
	}
	int count = 0;
	for (int i = 1; i <= V; ++i)
		if (lucky[i])
			++count;
	return count;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	int T;
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}