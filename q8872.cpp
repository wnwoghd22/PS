#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

typedef long long int ll;
const int LEN = 1e5;
const ll INF = 1e10;

std::vector<std::pair<int, ll>> graph[LEN];
std::priority_queue<ll> r; // radius of tree
bool checked[LEN];
int N, M, L, prior[LEN], _u, _v, t;
ll dist[LEN], max_dist, max_diameter;

void dfs(int v) {
	for (const auto& [u, d] : graph[v]) {
		if (checked[u]) continue;
		checked[u] = true;
		dist[u] = dist[v] + d;
		if (dist[u] > max_dist) {
			_u = u, max_dist = dist[u];
		}
		dfs(u);
	}
}
void dfs_diameter(int u) {
	for (const auto& [v, d] : graph[u]) {
		if (~prior[v]) continue;
		prior[v] = u;
		dist[v] = dist[u] + d;
		if (dist[v] > max_dist) {
			_v = v, max_dist = dist[v];
		}
		dfs_diameter(v);
	}
}
ll get_radius(int u) {
	dist[u] = max_dist = 0; _u = u;
	checked[u] = true;
	dfs(u);
	dist[_u] = max_dist = 0; _v = _u;
	prior[_u] = true;
	dfs_diameter(_u);
	max_diameter = std::max(max_diameter, max_dist);
	if (_u == _v) return 0;
	ll _r = INF, _d = max_dist;
	for (int i = _v; i != _u; i = prior[i]) {
		_r = std::min(_r, std::max(dist[i], _d - dist[i]));
	}
	return _r;
}

int main() { // dfs 3 times ... O(3*|V|)
	memset(prior, -1, sizeof prior);
	std::cin >> N >> M >> L;
	while (M--) {
		std::cin >> _u >> _v >> t;
		graph[_u].push_back({ _v, t });
		graph[_v].push_back({ _u, t });
	}
	for (int i = 0; i < N; ++i) {
		if (!checked[i])
			r.push(get_radius(i));
	}
	ll r1, r2, r3;
	max_dist = r1 = r.top(); r.pop();
	if (!r.empty()) r2 = r.top(), r.pop(), max_dist += r2 + L;
	if (!r.empty()) r3 = r.top(), max_dist = std::max(max_dist, r2 + r3 + L * 2);
	std::cout << std::max(max_dist, max_diameter);
}