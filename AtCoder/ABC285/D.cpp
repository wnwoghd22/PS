#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

const int MAX = 200001;
std::map<std::string, int> dict;
std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;
int N, idx;
std::string s, t;

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
		std::sort(scc.begin(), scc.end());
		SCC.push_back(scc);
	}
	return parent;
}


int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> s >> t;
		if (dict.find(s) == dict.end()) dict[s] = ++idx;
		if (dict.find(t) == dict.end()) dict[t] = ++idx;
		int u = dict[s], v = dict[t];
		graph[u].push_back(v);
	}
	for (int i = 1; i <= idx; ++i) {
		if (!checked[i]) dfs(i);
	}
	bool result = true;
	for (std::vector<int>& scc : SCC) {
		if (scc.size() > 1) {
			result = false;
			break;
		}
	}
	std::cout << (result ? "Yes" : "No");
}