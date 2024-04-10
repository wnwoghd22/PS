#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int LEN = 1e5 + 1;
const int INF = 1e9 + 7;

struct Edge {
	int v, w;
	bool operator<(const Edge& r) const { return w > r.w; }
};
std::vector<Edge> graph[LEN];
std::priority_queue<Edge> pq;
Edge dist[LEN];
int vp, vptr[LEN], cm[LEN], vn[LEN];

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

int s[LEN], e[LEN], l[LEN], r[LEN];
int qp, qptr[LEN], qi[LEN], qn[LEN];
bool visited[LEN];

int N, M, K, Q, R;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M >> K >> Q;
	for (int i = 0, u, v, w; i < M; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	for (int i = 1; i <= N; ++i) dist[i] = { i, INF };
	for (int i = 0, u; i < K; ++i) {
		std::cin >> u;
		dist[u].w = 0; pq.push({ u, 0 });
	}
	while (pq.size()) {
		int u = pq.top().v, d = pq.top().w; pq.pop();
		if (dist[u].w < d) continue;
		for (const Edge& e : graph[u]) {
			if (d + e.w < dist[e.v].w) {
				dist[e.v].w = d + e.w;
				pq.push({ e.v, d + e.w });
			}
		}
	}
	std::sort(dist + 1, dist + N + 1);
	// for (int i = 1; i <= N; ++i)
	//	std::cout << dist[i].v << ' ' << dist[i].w << '\n';
	memset(vptr, -1, sizeof vptr);
	for (int i = 1, j = -1; i <= N; ++i) {
		if (dist[i].w ^ j)
			j = cm[vp++] = dist[i].w;
		vn[i] = vptr[vp - 1];
		vptr[vp - 1] = i;
	}
	// for (int i = 0; i < vp; ++i)
	//	std::cout << vptr[i] << ' ' << cm[i] << '\n';

	for (int i = 0; i < Q; ++i) {
		std::cin >> s[i] >> e[i];
		r[i] = vp;
	}
	while (1) {
		R = qp = 0;
		memset(qptr, -1, sizeof qptr);
		for (int i = 0, m; i < Q; ++i) {
			if (l[i] < r[i]) {
				++R;
				m = l[i] + r[i] >> 1;
				qn[qp] = qptr[m];
				qi[qp] = i;
				qptr[m] = qp++;
			}
		}
		if (!R) break;

		memset(p, -1, sizeof p);
		memset(visited, 0, sizeof visited);
		for (int m = 0; m < vp; ++m) {
			int o = vptr[m];
			while (~o) {
				int u = dist[o].v;
				visited[u] = 1;
				for (const Edge& e : graph[u]) {
					if (visited[e.v])
						join(u, e.v);
				}
				o = vn[o];
			}
			int q = qptr[m];
			while (~q) {
				int i = qi[q];
				if (find(s[i]) == find(e[i])) r[i] = m;
				else l[i] = m + 1;
				q = qn[q];
			}
		}
	}
	for (int i = 0; i < Q; ++i)
		std::cout << cm[r[i]] << '\n';
}