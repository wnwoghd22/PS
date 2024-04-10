#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

const int MAX = 20'001;

std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;
int group[MAX];
int idx, order[MAX];
std::stack<int> _stack;

inline int get_index(int i) { return abs(i) * 2 - (i < 0); }
inline int get_inverse(int idx) { return (idx + (idx & 1)) / 2; }
inline int get_opposite(int idx) { return idx & 1 ? idx + 1 : idx - 1; }

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
	int V, E;
	std::cin.tie(0)->sync_with_stdio(0);

	while (std::cin >> E >> V) {
		for (std::vector<int>& v : graph) v.clear();
		memset(checked, 0, sizeof checked);
		SCC.clear();
		memset(group, 0, sizeof group);
		idx = 0;
		memset(order, 0, sizeof order);
		_stack = std::stack<int>();

		while (E--) {
			int a, b;
			std::cin >> a >> b;
			graph[get_index(-a)].push_back(get_index(b));
			graph[get_index(-b)].push_back(get_index(a));
		}

		for (int i = 1; i <= 2 * V; ++i) {
			if (!checked[i]) dfs(i);
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

		std::cout << (result ? "^_^" : "OTL") << '\n';
	}
}