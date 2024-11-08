#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

const int MAX = 1'000'001;

std::vector<int> graph[MAX];
int checked[MAX];
int results[MAX];
int scc, group[MAX];
std::pair<int, int> P[MAX];
inline int get_index(int i) { return abs(i) * 2 - (i < 0); }
inline int get_inverse(int idx) { return (idx + (idx & 1)) / 2; }
inline int get_opposite(int idx) { return idx & 1 ? idx + 1 : idx - 1; }

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
		while (true) {
			int e = _stack.top(); _stack.pop();
			group[e] = scc;
			checked[e] = true;
			if (e == v) break;
		}
		scc++;
	}
	return parent;
}

int main() {
	int V, E;
	std::cin >> E >> V;

	while (E--) {
		int a, sa, b, sb;
		std::cin >> a >> sa >> b >> sb;
		if (!sa) a *= -1;
		if (!sb) b *= -1;
		graph[get_index(-a)].push_back(get_index(b));
		graph[get_index(-b)].push_back(get_index(a));
	}

	for (int i = 1; i <= 2 * V; ++i) {
		if (!checked[i]) dfs(i);
	}

	bool result = true;
	for (int i = 1; i <= V; ++i) {
		if (group[get_index(i)] == group[get_index(-i)]) {
			result = false;
		}
	}

	if (result) {
		memset(results, -1, sizeof results);

		for (int i = 1; i <= V * 2; ++i) {
			P[i] = { group[i], i };
		}
		std::sort(P + 1, P + V * 2 + 1);

		for (int i = V * 2; i >= 1; --i) {
			int v = P[i].second;
			if (results[get_inverse(v)] == -1) {
				results[get_inverse(v)] = v & 1;
			}
		}
		for (int i = 1; i <= V; ++i) std::cout << results[i] << '\n';
	}
	else std::cout << "IMPOSSIBLE";
}