#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;
int N, M, Q, A, W, seg_tree[LEN * 4];
void update(int l, int r, int d, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i] += d;
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
}
int get(int x, int s = 1, int e = N, int i = 1) {
	if (e < x || x < s) return 0;
	if (s == e) return seg_tree[i];
	int m = s + e >> 1;
	return seg_tree[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int ord, in[LEN], out[LEN];
void dfs_euler(int u, int p = 0) {
	in[u] = ++ord;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		dfs_euler(v, u);
	}
	out[u] = ord;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M >> A;
	for (int i = 2; i <= N; ++i) {
		std::cin >> A;
		graph[A].push_back(i);
	}
	dfs_euler(1);
	while (M--) {
		std::cin >> Q;
		if (Q == 1) std::cin >> A >> W, update(in[A], out[A], W);
		if (Q == 2) std::cin >> A, std::cout << get(in[A]) << '\n';
	}
}