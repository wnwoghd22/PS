#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

const int MAX = 100'001;

std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;

int group[MAX];
std::vector<int> scc_graph[MAX];
int incoming[MAX];

int idx, order[MAX];
std::stack<int> _stack;

int dfs(int v) {
	order[v] = ++idx;
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
		SCC.push_back(scc);
	}
	return parent;
}

int main() {
	int T;
	std::cin >> T;

	while (T--) {
		for (auto& v : graph) v.clear();
		memset(checked, 0, sizeof checked);
		SCC.clear();

		memset(group, 0, sizeof group);
		for (auto& v : scc_graph) v.clear();
		memset(incoming, 0, sizeof incoming);

		idx = 0;
		memset(order, 0, sizeof order);
		_stack = std::stack<int>();

		int V, E;
		std::cin >> V >> E;

		while (E--) {
			int a, b;
			std::cin >> a >> b;
			graph[a].push_back(b);
		}

		for (int i = 1; i <= V; ++i)
			if (!checked[i]) dfs(i);

		for (int i = 0; i < SCC.size(); ++i) {
			std::cout << "SCC " << i << ": ";
			for (const int& e : SCC[i]) {
				std::cout << e << ' ';
				group[e] = i;
			}
		}

		for (int i = 1; i <= V; ++i) std::cout << group[i] << ' ';

		for (int i = 1; i <= V; ++i) {
			for (const int& e : graph[i]) {
				int from = group[i], to = group[e];
				if (from == to) continue;
				std::cout << "from: " << from << " to: " << to << '\n';
				if (std::find(scc_graph[from].begin(), scc_graph[from].end(), to) == scc_graph[from].end()) {
					scc_graph[from].push_back(to);
					incoming[to]++;
				}
			}
		}
		int result = 0;

		std::cout << "\nincoming: ";
		for (int i = 0; i < SCC.size(); ++i) {
			std::cout << incoming[i] << ' ';
			if (!incoming[i]) ++result;
		}

		std::cout << result << '\n';
	}
}