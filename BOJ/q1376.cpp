#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
const int LEN = 1e5 + 1;

std::priority_queue<int> pq[LEN];
std::vector<int> g[LEN];
int bs(const std::vector<int>& v, int x) {
	int l = 0, r = v.size() - 1, m;
	while (l <= r) {
		m = l + r >> 1;
		if (v[m] == x) return m;
		if (v[m] > x) r = m - 1;
		else l = m + 1;
	}
	return -1;
}

struct fenwick {
	int size;
	std::vector<int> t;
	ll sum(int i) {
		ll result = 0;
		while (i > 0) {
			result += t[i];
			i -= i & -i;
		}
		return result;
	}
	void update(int i, ll d) {
		while (i <= size) {
			t[i] += d;
			i += i & -i;
		}
	}
	void init(int n) {
		size = n;
		t.resize(n + 1);
		for (int i = 1; i <= n; ++i) update(i, 1);
	}

	int bs(ll x) {
		int l = 1, r = size, m, result = size;
		while (l <= r) {
			m = l + r >> 1;
			if (sum(m) >= x) {
				result = std::min(m, result);
				r = m - 1;
			}
			else l = m + 1;
		}
		return result;
	}
} f[LEN];

int N, M;
int max[LEN], cur[LEN];
bool visited[LEN];

void dfs(int u) {
	if (visited[u]) return;
	visited[u] = 1;
	std::cout << u << ' ';
	for (const int& v : g[u]) { f[v].update(bs(g[v], u) + 1, -1); cur[v]--; }
	while (cur[u]) {
		// std::cout << "cur size: " << cur[u] << '\n';
		// std::cout << "next: " << (cur[u] & 1 ? cur[u] >> 1 : 0) + 1 << "th\n";
		// std::cout << "next: " << g[u][f[u].bs((cur[u] & 1 ? cur[u] >> 1 : 0) + 1) - 1] << '\n';
		dfs(g[u][f[u].bs((cur[u] & 1 ? cur[u] >> 1 : 0) + 1) - 1]);
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		if (u == v) continue;
		pq[u].push(-v);
		pq[v].push(-u);
	}
	for (int u = 1; u <= N; ++u) {
		while (pq[u].size()) {
			if (g[u].empty() || g[u].back() != -pq[u].top())
				g[u].push_back(-pq[u].top());
			pq[u].pop();
		}
		max[u] = cur[u] = g[u].size();
		f[u].init(max[u]);
	}
	
	dfs(1);
}