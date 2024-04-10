#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int LEN = 4001;
typedef long long ll;

int T, N, M, K;

const int MAX = 4001;
inline int get_index(int x, bool b) { return (x - 1) << 1 | b; }
inline int get_neg(int i) { return i ^ 1; }
inline int get_inv(int i) { return (i >> 1) + 1; }
std::vector<int> graph[MAX];
int checked[MAX];
std::vector<std::vector<int>> SCC;
int group[MAX];
int idx, order[MAX];
std::vector<int> stack;

int dfs(int u) {
	order[u] = ++idx;
	int min = order[u];
	stack.push_back(u);
	for (const int& v : graph[u]) {
		if (!order[v]) min = std::min(min, dfs(v));
		else if (!checked[v]) min = std::min(min, order[v]);
	}
	if (min == order[u]) { // cycle
		std::vector<int> scc;
		while (true) {
			int e = stack.back(); stack.pop_back();
			scc.push_back(e);
			checked[e] = true;
			if (e == u) break;
		}
		SCC.push_back(scc);
	}
	return min;
}

bool solve() {
	SCC.clear();
	for (std::vector<int>& v : graph) v.clear();
	memset(checked, 0, sizeof checked);
	memset(order, 0, sizeof order);
	idx = 0;

	std::cin >> N >> M >> K;
	for (int i = 0, a, b, c, d, x1, x2, y1, y2; i < K; ++i) {
		std::cin >> a >> b >> c >> d;
		if (a == c && b == d) continue;
		
		x1 = get_index(a, b < d), x2 = get_index(c, b < d);
		y1 = get_index(b + N, a < c), y2 = get_index(d + N, a < c);

		if (a == c) graph[get_neg(x1)].push_back(x1);
		else if (b == d) graph[get_neg(y1)].push_back(y1);
		else {
			graph[get_neg(x1)].push_back(y1); graph[get_neg(y1)].push_back(x1);
			graph[get_neg(x1)].push_back(x2); graph[get_neg(x2)].push_back(x1);
			graph[get_neg(x2)].push_back(y2); graph[get_neg(y2)].push_back(x2);
			graph[get_neg(y1)].push_back(y2); graph[get_neg(y2)].push_back(y1);
		}
	}
	
	for (int i = 0; i < N + M << 1; ++i) {
		if (!checked[i]) dfs(i);
	}

	for (int i = 0; i < SCC.size(); ++i) {
		for (const int& v : SCC[i]) {
			// std::cout << v << ' ' << i << '\n';
			group[v] = i;
		}
	}

	bool flag = true;
	for (int i = 1; i <= N + M; ++i) {
		if (group[get_index(i, true)] == group[get_index(i, false)]) {
			flag = false;
			break;
		}
	}
	return flag;
}

int main() {
	std::cin >> T;
	while (T--)
		std::cout << (solve() ? "Yes\n" : "No\n");
}