#include <iostream>
#include <algorithm>
#include <vector>

#include <bitset>

typedef long long ll;
const int LEN = 1e6;
const int V_LEN = 30;

int N, S;
std::vector<int> graph[V_LEN];
int size[V_LEN], cent[2];

ll h[LEN];

int get_size(int u, int p = -1) {
	size[u] = 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		size[u] += get_size(v, u);
	}
	return size[u];
}
int get_cent(int u, int s, int p = -1) {
	for (const int& v : graph[u]) {
		if (v == p) continue;
		if (size[v] > s)
			return get_cent(v, s, u);
	}
	return u;
}
int get_extra_cent(int c, int s) {
	for (const int& e : graph[c]) {
		if (size[c] - size[e] <= s)
			return e;
	}
	return -1;
}

ll dfs_hash(int u, int p = -1) {
	ll key = 1;
	std::vector<ll> sub;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		sub.push_back(dfs_hash(v, u));
	}
	std::sort(sub.begin(), sub.end());
	for (const ll& k : sub) {
		for (ll i = k; i; i >>= 1) key <<= 1;
		key |= k;
	}
	return key << 1;
}

ll ahu() {
	for (std::vector<int>& v : graph) v.clear();

	std::cin >> S;
	for (int i = 1, u, v; i < S; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	get_size(0);
	cent[0] = get_cent(0, size[0] >> 1);
	get_size(cent[0]);
	cent[1] = get_extra_cent(cent[0], size[cent[0]] >> 1);

	ll key = dfs_hash(cent[0]);
	if (~cent[1]) key = std::min(key, dfs_hash(cent[1]));

	return key;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;

	for (int i = 0; i < N; ++i) h[i] = ahu();
	std::sort(h, h + N);

	for (int i = 0; i < N; ++i) std::cout << std::bitset<64>(h[i]) << '\n';

	int uniq = 1;
	for (int i = 1; i < N; ++i)
		if (h[i - 1] ^ h[i]) ++uniq;
	std::cout << uniq;
}