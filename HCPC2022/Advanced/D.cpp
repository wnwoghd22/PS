#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>

const int MAX = 200'001;

std::vector<int> graph[MAX];
int checked[MAX];

std::vector<std::vector<int>> SCC;
std::set<int> graph_SCC[MAX];
int group[MAX];
int incoming[MAX];
int depth[MAX];
int start_point;
int V, E;

int dfs(int v) {
	static int idx = 1, order[MAX];
	static std::stack<int> _stack;
	order[v] = idx++;
	int parent = order[v];
	_stack.push(v);
	for (const int& u : graph[v]) {
		if (!order[u]) parent = std::min(parent, dfs(u));
		else if (!checked[u]) parent = std::min(parent, order[u]);
	}
	if (parent == order[v]) { // cycle
		std::vector<int> scc;
		while (true) {
			int e = _stack.top(); _stack.pop();
			scc.push_back(e);
			checked[e] = true;
			if (e == v) break;
		}
		std::sort(scc.begin(), scc.end());
		SCC.push_back(scc);
	}
	return parent;
}

int topological_sort() {
	int max_count = 1;
	for (int i = 0; i < SCC.size(); ++i) { // preporcess
		for (const int& e : SCC[i]) {
			group[e] = i;
		}
	}
	for (int i = 1; i <= V; ++i) {
		for (const int& e : graph[i]) {
			int from = group[i], to = group[e];
			if (from == to) continue;
			if (graph_SCC[from].find(to) == graph_SCC[from].end()) {
				graph_SCC[from].insert(to);
				incoming[to]++;
			}
		}
	}
	std::queue<int> Q;
	for (int i = 0; i < SCC.size(); ++i) {
		if (!incoming[i]) {
			start_point = i;
			depth[i] = 1;
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (const int& v : graph_SCC[u]) {
			if (!--incoming[v]) {
				depth[v] = depth[u] + 1;
				max_count = std::max(depth[v], max_count);
				Q.push(v);
			}
		}
	}
	return max_count;
}

int main() {
	std::cin >> V >> E;

	while (E--) {
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
	}

	for (int i = 1; i <= V; ++i) {
		if (!checked[i]) dfs(i);
	}

	if (topological_sort() == SCC.size()) {
		std::cout << SCC[start_point].size() << '\n';
		std::sort(SCC[start_point].begin(), SCC[start_point].end());
		for (const int& e : SCC[start_point]) std::cout << e << ' ';
	}
	else std::cout << 0;
}