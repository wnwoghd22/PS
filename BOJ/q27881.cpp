#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>

typedef long long ll;
const int LEN = 1e5;
const ll INF = 2e17;
struct Info {
	int u; ll dist; 
	bool operator<(const Info& r) const { return dist > r.dist; }
};
std::priority_queue<Info> pq;

int N, Q, k;
ll p[LEN << 2];
ll edge[3][4];
ll dist[3][LEN << 2];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0; i < N << 2; ++i) std::cin >> p[i];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
			std::cin >> edge[j][i];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < N << 2; ++j) dist[i][j] = INF;
		for (int j = 0; j < 4; ++j) {
			dist[i][(j + 1) * N - 1] = edge[i][j];
			pq.push({ (j + 1) * N - 1, edge[i][j] });
		}
		while (pq.size()) {
			int u = pq.top().u;
			ll cur = pq.top().dist;
			pq.pop();
			if (cur > dist[i][u]) continue;
			int l = (u - 1 + (N << 2)) % (N << 2);
			if (dist[i][u] + p[l] < dist[i][l]) {
				dist[i][l] = dist[i][u] + p[l];
				pq.push({ l, dist[i][l] });
			}
			int r = (u + 1) % (N << 2);
			if (dist[i][u] + p[u] < dist[i][r]) {
				dist[i][r] = dist[i][u] + p[u];
				pq.push({ r, dist[i][r] });
			}
		}
	}
	std::cin >> Q;
	while (Q--) {
		std::cin >> k; --k;
		std::cout << std::min({ dist[0][k], dist[1][k], dist[2][k] }) << '\n';
	}
}