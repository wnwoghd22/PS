#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <set>

const int LEN = 1001;

struct P {
	int x, y;
	bool operator<(const P& r) const {
		return x == r.x ? y < r.y : x < r.x;
	}
};

int index = 0;
std::map<P, int> map;
int idx(const P& p) {
	if (map.find(p) == map.end()) {
		map[p] = ++index;
	}
	return map[p];
}

std::set<int> graph[LEN];
int E, V, F, visited[LEN];
void dfs(int u, int p = 0) {
	visited[u] = visited[p] + 1;
	++V;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		if (visited[v]) {
			if (visited[v] < visited[u]) { // cycle
				++E;
			}
		}
		else {
			++E;
			dfs(v, u);
		}
	}
}

int N;
char S[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> S;

	for (int i = 0, x = 0, y = 0; i < N; ++i) {
		int u = idx({ x, y });
		if (S[i] == 'N') ++y;
		if (S[i] == 'S') --y;
		if (S[i] == 'E') ++x;
		if (S[i] == 'W') --x;
		int v = idx({ x, y });
		graph[u].insert(v);
		graph[v].insert(u);
	}
	dfs(1);
	F = 1 - V + E;
	std::cout << F;
}
