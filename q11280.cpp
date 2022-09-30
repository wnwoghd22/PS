#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAX = 20'001;

std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;
int group[20'001];
inline int get_index(int i) { return abs(i) * 2 - (i < 0); }

int dfs(int v) {
	static int idx, order[MAX];
	static std::stack<int> _stack;
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
	int V, E;
	std::cin >> V >> E;

	while (E--) {
		int a, b;
		std::cin >> a >> b;
		graph[get_index(-a)].push_back(get_index(b));
		graph[get_index(-b)].push_back(get_index(a));
	}
	for (int i = 1; i <= 2 * V; ++i) {
		std::cout << "V " << i << ": ";
		for (const int& u : graph[i])
			std::cout << u << ' ';
		std::cout << '\n';
	}

	for (int i = 1; i <= 2 * V; ++i) {
		if (!checked[i]) dfs(i);
	}

	std::cout << SCC.size() << '\n';
	for (std::vector<int>& scc : SCC) {
		for (const int& v : scc)
			std::cout << v << ' ';
		std::cout << "-1\n";
	}

	for (int i = 0; i < SCC.size(); ++i) {
		for (const int v : SCC[i]) {
			group[v] = i;
		}
	}

	bool result = true;
	for (int i = 1; i <= V; ++i) {
		if (group[get_index(i)] == group[get_index(-i)]) {
			result = false;
		}
	}

	std::cout << result;
}