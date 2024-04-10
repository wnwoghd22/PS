#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

const int MAX = 20'001;

std::vector<int> graph[MAX];
int checked[MAX];
int results[MAX];
std::vector<std::vector<int>> SCC;
int group[MAX];
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
		int n1, n2, n3;
		char c1, c2, c3;
		std::cin >> n1 >> c1 >> n2 >> c2 >> n3 >> c3;
		// R: true, B: false
		if (c1 != 'R') n1 *= -1;
		if (c2 != 'R') n2 *= -1;
		if (c3 != 'R') n3 *= -1;

		graph[get_index(-n1)].push_back(get_index(n2));
		graph[get_index(-n1)].push_back(get_index(n3));

		graph[get_index(-n2)].push_back(get_index(n1));
		graph[get_index(-n2)].push_back(get_index(n3));

		graph[get_index(-n3)].push_back(get_index(n1));
		graph[get_index(-n3)].push_back(get_index(n2));
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

	if (!result) std::cout << -1;
	else if (result) {
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
		for (int i = 1; i <= V; ++i) std::cout << (results[i] ? 'R' : 'B');
	}
}