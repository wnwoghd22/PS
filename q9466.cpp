#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

const int MAX = 100'001;

std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;
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
		std::sort(scc.begin(), scc.end());
		SCC.push_back(scc);
	}
	return parent;
}

void solve() {
	SCC.clear();
	for (std::vector<int>& v : graph) v.clear();
	idx = 0;
	memset(checked, 0, sizeof checked);
	memset(order, 0, sizeof order);
	_stack = std::stack<int>();

	int V ,result;
	std::cin >> V; result = V;
	for (int v, u = 1; u <= V; ++u) {
		std::cin >> v;
		if (u != v) graph[u].push_back(v);
		else result--;
	}

	for (int i = 1; i <= V; ++i) {
		if (!checked[i]) dfs(i);
	}
	for (const auto& scc : SCC) {
		if (scc.size() > 1) result -= scc.size();
	}
	std::cout << result << '\n';
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}