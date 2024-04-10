#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
const int LEN = 500'001;
const ll INF = 2e17;

int N, Q;
struct Edge { int v, w; };
std::vector<Edge> graph[LEN];
int ord, in[LEN], out[LEN], level[LEN], parent[LEN][21];
ll dst[LEN];

void dfs_euler(int u, ll d = 0, int p = 0) {
	in[u] = ++ord;
	level[in[u]] = level[in[p]] + 1;
	parent[in[u]][0] = in[p];
	dst[in[u]] = d;
	for (int i = 1, v = in[p]; v; v = parent[in[u]][i++])
		parent[in[u]][i] = parent[v][i - 1];
	for (const Edge& e : graph[u]) {
		if (e.v == p) continue;
		dfs_euler(e.v, d + e.w, u);
	}
	out[in[u]] = ord;
}

int lca(int u, int v) {
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = 20; i >= 0; --i)
			if (level[parent[v][i]] >= level[u])
				v = parent[v][i];
	}
	int l = u;
	if (u ^ v) {
		for (int i = 20; i >= 0; --i) {
			if (parent[u][i] ^ parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
			l = parent[u][i];
		}
	}
	return l;
}

int lcaa[LEN], l_len, temp[LEN * 3], t_len, color[LEN];
ll min;
struct Info { ll x, y; };
Info f(int u) {
	ll blue = color[u] == 1 ? 0 : INF;
	ll green = color[u] == 2 ? 0 : INF;
	color[u] = 0;
	while (ord <= l_len && lcaa[ord] <= out[u]) {
		int v = lcaa[ord++];
		Info sub = f(v);
		blue = std::min(blue, sub.x + dst[v] - dst[u]);
		green = std::min(green, sub.y + dst[v] - dst[u]);
	}
	min = std::min(min, blue + green);
	return { blue, green };
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 1, a, b, d; i < N; ++i) {
		std::cin >> a >> b >> d;
		++a, ++b;
		graph[a].push_back({ b, d });
		graph[b].push_back({ a, d });
	}
	dfs_euler(1);

	for (int i = 0, s, t, x, y; i < Q; ++i) {
		ord = l_len = t_len = 0;
		std::cin >> s >> t;
		for (int j = 0; j < s; ++j) {
			std::cin >> x; ++x; color[in[x]] = 1;
			temp[t_len++] = in[x];
		}
		for (int j = 0; j < t; ++j) {
			std::cin >> y; ++y; color[in[y]] = 2;
			temp[t_len++] = in[y];
		}
		std::sort(temp, temp + t_len);
		for (int i = 1; i < t_len; ++i) {
			lcaa[l_len++] = lca(temp[i - 1], temp[i]);
		}
		for (int i = 0; i < l_len; ++i) temp[t_len++] = lcaa[i];
		std::sort(temp, temp + t_len);
		lcaa[l_len = 0] = temp[0];
		for (int i = 1; i < t_len; ++i)
			if (temp[i - 1] ^ temp[i])
				lcaa[++l_len] = temp[i];
		min = INF;
		f(1);
		std::cout << min << '\n';
	}
}