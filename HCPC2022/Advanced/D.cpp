#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAX = 200'001;

std::vector<int> graph[MAX];
int checked[MAX];

std::vector<std::vector<int>> SCC;
std::vector<int> graph_SCC[MAX];
int group[MAX];
int incoming[MAX];
int outgoing[MAX];

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

int main() {
	int V, E;
	std::cin >> V >> E;

	while (E--) {
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
	}

	for (int i = 1; i <= V; ++i) {
		if (!checked[i]) dfs(i);
	}

	if (SCC.size() == 1) {
		std::cout << SCC[0].size() << '\n';
		std::sort(SCC[0].begin(), SCC[0].end());
		for (const int& e : SCC[0]) std::cout << e << ' ';
	}
	else {
		for (int i = 0; i < SCC.size(); ++i) { // preporcess
			for (const int& e : SCC[i]) {
				group[e] = i;
			}
		}
		for (int i = 1; i <= V; ++i) {
			for (const int& e : graph[i]) {
				int from = group[i], to = group[e];
				if (from == to) continue;
				graph_SCC[from].push_back(to);
				incoming[to]++;
				outgoing[from]++;
			}
		}
		int start_point = -1, start_count = 0, end_count = 0;
		for (int i = 0; i < SCC.size(); ++i) {
			if (!incoming[i]) start_point = i, start_count++;
			if (!outgoing[i]) end_count++;
		}
		if (start_count > 1 || end_count > 1) std::cout << 0;
		else {
			std::cout << SCC[start_point].size() << '\n';
			std::sort(SCC[start_point].begin(), SCC[start_point].end());
			for (const int& e : SCC[start_point]) std::cout << e << ' ';
		}
	}
}