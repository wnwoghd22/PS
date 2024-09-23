#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAX = 200'001;

std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;

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

	std::cout << (SCC.size() == 1 ? "Yes" : "No");
}