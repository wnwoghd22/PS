#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long int ll;
const int LEN = 200'001;
ll seg_tree[LEN * 4];
int N, C, Q, x, y;

void update(int l, int r, int a, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i]+= a;
		return;
	}
	int m = s + e >> 1;
	update(l, r, a, s, m, i << 1);
	update(l, r, a, m + 1, e, i << 1 | 1);
}

ll get_sum(int x, int s = 1, int e = N, int i = 1) {
	if (e < x || x < s) return 0;
	if (s == e) return seg_tree[i];
	int m = s + e >> 1;
	return seg_tree[i] + get_sum(x, s, m, i << 1) + get_sum(x, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int level[LEN];
int ord, in[LEN], out[LEN];

void dfs_euler(int u, int p = 0) {
	in[u] = ++ord;
	level[u] = level[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		dfs_euler(v, u);
	}
	out[u] = ord;
}

void q1(int a) { update(1, in[a], 1); }
ll q2(int a) { return level[a] * (get_sum(out[a]) - get_sum(in[a] - 1)); }

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> C;
	for (int i = 1; i < N; ++i) {
		std::cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs_euler(C);

	std::cin >> Q;
	while (Q--) {
		std::cin >> x >> y;
		if (x == 1) q1(y);
		else if (x == 2) std::cout << q2(y) << '\n';
	}
}