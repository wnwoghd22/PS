#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <queue>

const int LEN = 30'001;
const int INF = 1e9;
struct Info {
	int u, d;
	bool operator<(const Info& r) const { return d > r.d; }
};
int N, M, B, P, S, E, p[LEN], dist[LEN];
std::set<int> ps[LEN];

int dijkstra(const int s, const int e) {
	std::priority_queue<Info> pq;
	for (int i = 0; i < N; ++i) dist[i] = INF;
	dist[s] = 0;
	pq.push({ s, 0 });
	while (!pq.empty()) {
		Info i = pq.top(); pq.pop();
		int u = i.u, d = i.d;
		if (d > dist[u]) continue;
		for (const int& p : ps[u]) {
			for (int i = 1, v = u + p; v < N; ++i, v += p) {
				if (ps[v].size() && d + i < dist[v]) {
					dist[v] = d + i;
					pq.push({ v, d + i });
				}
				if (ps[v].find(p) != ps[v].end()) break;
			}
			for (int i = 1, v = u - p; v >= 0; ++i, v -= p) {
				if (ps[v].size() && d + i < dist[v]) {
					dist[v] = d + i;
					pq.push({ v, d + i });
				}
				if (ps[v].find(p) != ps[v].end()) break;
			}
		}
	}
	return dist[e];
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	
	--M;
	std::cin >> B >> P;
	S = B; ps[B].insert(P);

	--M;
	std::cin >> B >> P;
	E = B; ps[B].insert(P);

	while (M--) {
		std::cin >> B >> P;
		ps[B].insert(P);
	}
	int result = dijkstra(S, E);

	std::cout << (result != INF ? result : -1);
}