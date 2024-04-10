#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>

const int MAX = 500'001;

std::vector<int> graph[MAX];
int weight[MAX];
bool has_restaurant[MAX];
bool checked[MAX];
std::vector<std::vector<int>> SCC;
int startPos;

int group[MAX];
int scc_weight[MAX];
bool scc_has_restaurant[MAX];
std::vector<int> scc_graph[MAX];
std::vector<int> prior[MAX];
int incoming[MAX];
int scc_start_pos;
int dp[MAX];

int idx, order[MAX];
std::stack<int> _stack;
int N;

int topological_sort() {
	std::queue<int> q;
	int max_weight = 0;
	bool flag = false;

	for (int i = 0; i < SCC.size(); ++i) {
		if (!incoming[i]) {
			std::cout << "push " << i << '\n';
			q.push(i);
		}
	}
	dp[scc_start_pos] = scc_weight[scc_start_pos];

	while (!q.empty()) {
		int v = q.front(); q.pop();
		if (v == scc_start_pos) flag = true;

		for (const int& u : scc_graph[v]) {
			if (flag) {
				dp[u] = std::max(dp[u], dp[v] + scc_weight[u]);
			}

			if (!--incoming[u]) {
				q.push(u);
			}
		}
	}
	for (int i = 0; i < SCC.size(); ++i) {
		if (scc_has_restaurant[i]) {
			max_weight = std::max(max_weight, dp[i]);
		}
	}

	return max_weight;
}

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
	std::cin >> V >> E;

	while (E--) {
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
	}

	for (int i = 1; i <= V; ++i) {
		std::cin >> weight[i];
	}

	std::cin >> startPos >> E;
	while (E--) {
		int P;
		std::cin >> P;
		has_restaurant[P] = true;
	}

	for (int i = 1; i <= V; ++i)
		if (!checked[i]) dfs(i);

	for (int i = 0; i < SCC.size(); ++i) { // preporcess
		for (const int& e : SCC[i]) {
			std::cout << e << ' ';
			group[e] = i;
			scc_weight[i] += weight[e];
			if (has_restaurant[e]) scc_has_restaurant[i] = true;
			if (e == startPos) scc_start_pos = i;
		}
		std::cout << "SCC " << i << ": " << scc_has_restaurant[i] << ' ' << scc_weight[i] << '\n';
	}

	std::cout << "group: ";
	for (int i = 1; i <= V; ++i) std::cout << group[i] << ' ';
	std::cout << '\n';
	std::cout << "SCC Start: " << scc_start_pos << '\n';

	for (int i = 1; i <= V; ++i) {
		for (const int& e : graph[i]) {
			int from = group[i], to = group[e];
			if (from == to) continue;
			std::cout << "from: " << from << " to: " << to << '\n';
			if (std::find(scc_graph[from].begin(), scc_graph[from].end(), to) == scc_graph[from].end()) {
				scc_graph[from].push_back(to);
				incoming[to]++;
				prior[to].push_back(from);
			}
		}
	}
	std::cout << topological_sort();
}