#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;
const int LEN = 2e5 + 1;

int N;
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

std::vector<int> graph[LEN];
int parent[LEN], bcc[LEN];
ll w[LEN], S[LEN], SS[LEN];

void dfs(int u, int p) {
	bcc[u] = u;
	parent[u] = p;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		dfs(v, u);
	}
}

ll update(int u, ll d) {
	int p = parent[u];
	ll cnt = 0;

	cnt += (S[p] - w[u]) * d * 2;
	S[p] += d;

	if (parent[p]) {
		int pp = bcc[find(p)];
		cnt += w[pp] * d * 2;
		SS[pp] += d;
	}

	cnt += SS[u] * d * 2;

	cnt -= (w[u] + 1) * w[u] * (w[u] - 1);
	w[u] += d;
	cnt += (w[u] + 1) * w[u] * (w[u] - 1);

	return cnt;
}

ll merge(int u) {
	int p = parent[u];
	int pp = bcc[find(p)];
	
	ll cnt = 0;

	S[p] -= w[u];
	cnt -= S[p] * w[u] * 2;
	SS[pp] -= w[u];
	cnt -= w[pp] * w[u] * 2;

	cnt -= w[u] * SS[u] * 2;
	cnt += w[pp] * SS[u] * 2;
	SS[pp] += SS[u];

	cnt -= (w[u] + 1) * w[u] * (w[u] - 1);
	cnt += update(pp, w[u]);
	
	bcc[u] = pp;
	// join(u, pp);
	::p[u] = pp;

	return cnt;
}

ll remove(int u) {
	ll cnt = 0;

	for (const int& v : graph[u]) {
		if (v == parent[u]) continue;
		cnt += merge(v);
	}
	cnt += update(bcc[find(u)], -1);

	return cnt;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(N, 0);
	memset(p, -1, sizeof p);

	ll result = 0;
	for (int i = 1; i < N; ++i) result += update(i, 1);

	std::cout << result << '\n';
	for (int i = 1; i < N; ++i) {
		result += remove(i);
		std::cout << result << '\n';
	}
}