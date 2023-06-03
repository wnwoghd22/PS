#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int LEN = 3001;
typedef long long ll;
struct Pos { ll x, y; } pos[LEN][2];

int N;

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { 
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y; 
}
bool intersect(Pos p1, Pos p2, Pos p3, Pos p4) {
	ll ccw1 = cross(p1, p2, p3), ccw2 = cross(p1, p2, p4);
	ll ccw3 = cross(p3, p4, p1), ccw4 = cross(p3, p4, p2);
	return ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0;
}

const int MAX = 6001;
inline int get_index(int x, bool b) { return (x - 1) << 1 | b; }
inline int get_neg(int i) { return i ^ 1; }
inline int get_inv(int i) { return (i >> 1) + 1; }
std::vector<int> graph[MAX];
int checked[MAX];
int val[MAX];
std::vector<std::vector<int>> SCC;
int group[MAX];
std::pair<int, int> P[MAX];
int idx, order[MAX];
std::vector<int> stack;
std::vector<int> results;

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

int main() {
	std::cin >> N;
	for (int n = 0; n < N; ++n) {
		for (int i = 1; i <= 3; ++i) {
			std::cin >> pos[n * 3 + i][0].x >> pos[n * 3 + i][0].y;
			std::cin >> pos[n * 3 + i][1].x >> pos[n * 3 + i][1].y;
		}
		graph[get_index(n * 3 + 1, false)].push_back(get_index(n * 3 + 2, true));
		graph[get_index(n * 3 + 1, false)].push_back(get_index(n * 3 + 3, true));

		graph[get_index(n * 3 + 2, false)].push_back(get_index(n * 3 + 1, true));
		graph[get_index(n * 3 + 2, false)].push_back(get_index(n * 3 + 3, true));

		graph[get_index(n * 3 + 3, false)].push_back(get_index(n * 3 + 1, true));
		graph[get_index(n * 3 + 3, false)].push_back(get_index(n * 3 + 2, true));
	}
	for (int i = 1; i < N * 3; ++i) {
		for (int j = i + 1; j <= N * 3; ++j) {
			if (intersect(pos[i][0], pos[i][1], pos[j][0], pos[j][1])) {
				// std::cout << "intersect: " << i << ' ' << j << '\n';
				graph[get_index(i, true)].push_back(get_index(j, false));
				graph[get_index(j, true)].push_back(get_index(i, false));
			}
		}
	}

	for (int i = 0; i < N * 6; ++i) {
		if (!checked[i]) dfs(i);
	}

	for (int i = 0; i < SCC.size(); ++i) {
		for (const int& v : SCC[i]) {
			// std::cout << v << ' ' << i << '\n';
			group[v] = i;
		}
	}

	bool flag = true;
	for (int i = 1; i <= N * 3; ++i) {
		if (group[get_index(i, true)] == group[get_index(i, false)]) {
			flag = false;
			break;
		}
	}
	if (!flag) std::cout << -1;
	else {
		memset(val, -1, sizeof val);

		for (int i = 0; i < N * 6; ++i) {
			P[i] = { group[i], i };
		}
		std::sort(P, P + N * 6);
		// for (int i = 0; i < N * 6; ++i) {
		// 	std::cout << P[i].first << ' ' << P[i].second << '\n';
		// }

		for (int i = N * 6 - 1; i >= 0; --i) {
			int v = P[i].second;
			if (val[get_inv(v)] == -1) {
				val[get_inv(v)] = ~v & 1;
			}
		}
		// for (int i = 0; i < N * 6; ++i) std::cout << val[i] << ' ';
		for (int i = 1; i <= N * 3; ++i) {
			if (!val[i])
				results.push_back(i);
		}
		std::cout << results.size() << '\n';
		for (const int& i : results) std::cout << i << ' ';
	}
}