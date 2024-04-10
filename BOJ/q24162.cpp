#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

const int LEN = 101;

struct Pos {
	int x, y;
	bool operator<(const Pos& p) const {
		if (x == p.x) return y < p.y;
		return x < p.x;
	}
} pos[LEN];

int cross(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x); }
int dot(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.x - p3.x) + (p2.y - p1.y) * (p4.y - p3.y); }
bool obtuse(const Pos& prev, const Pos& cur, const Pos& next) { return dot(prev, cur, cur, next) >= 0; }

int N, M, cost[LEN][LEN];
std::vector<int> graph[LEN];

struct Info {
	int u; // current node
	int p; // previous node
	int d; // cost
	bool operator<(const Info& r) const { return d > r.d; }
};

std::unordered_map<int, int> dp[LEN]; // dp[u][p]: from p, now u
std::priority_queue<Info> pq;

int dijkstra() {
	int result = 1e9;
	for (const int& v : graph[1]) {
		dp[v][1] = cost[1][v];
		pq.push({ v, 1, dp[v][1] });
	}
	while (pq.size()) {
		Info i = pq.top(); pq.pop();
		if (i.d > dp[i.u][i.p]) continue;
		if (i.u == 2) { result = std::min(result, i.d); continue; }
		for (const int& v : graph[i.u]) {
			if (obtuse(pos[i.p], pos[i.u], pos[v])) {
				if (dp[v].find(i.u) == dp[v].end() || i.d + cost[i.u][v] < dp[v][i.u]) {
					dp[v][i.u] = i.d + cost[i.u][v];
					pq.push({ v, i.u, dp[v][i.u] });
				}
			}
		}
	}
	if (dp[2].empty()) return -1;
	return result;
}

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) std::cin >> pos[i].x >> pos[i].y;
	for (int i = 0, u, v, c; i < M; ++i) {
		std::cin >> u >> v >> c;
		cost[u][v] = cost[v][u] = c;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	std::cout << dijkstra();
}