#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 100'001;

int N, K, J;

std::vector<int> graph[LEN];
int ord, in[LEN], out[LEN];
void dfs_euler(int u) {
	in[u] = ++ord;
	for (const int& v : graph[u])
		dfs_euler(v);
	out[u] = ord;
}

ll seg_tree[LEN << 2];
void update(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) { seg_tree[i] += d; return; }
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1); update(l, r, d, m + 1, e, i << 1 | 1);
}
ll get(int x, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return 0;
	if (s == e) return seg_tree[i];
	int m = s + e >> 1;
	return seg_tree[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

int singer[LEN];
std::vector<int> songs[LEN];
int cnt, ptr[LEN], np[LEN], l[LEN], r[LEN];

struct Data {
	int t, p, s;
	bool operator<(const Data& r) const { return t < r.t; }
} data[LEN];
int hi, dptr[LEN], nd[LEN], t[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K >> J;
	for (int v = 2, u; v <= N; ++v) {
		std::cin >> u;
		graph[u].push_back(v);
	}
	for (int i = 1; i <= N; ++i) {
		std::cin >> singer[i];
		songs[singer[i]].push_back(i);
	}
	for (int i = 0; i < K; ++i)
		std::cin >> data[i].t >> data[i].p >> data[i].s;

	dfs_euler(1);
	std::sort(data, data + K);
	memset(dptr, -1, sizeof dptr);
	for (int i = 0, j = 0; i < K - 1; ++i) {
		if (data[i].t ^ j)
			t[hi++] = j = data[i].t;
		nd[i] = dptr[hi - 1]; dptr[hi - 1] = i;
	}
	t[hi] = -1;
	for (int i = 1; i <= N; ++i) r[i] = hi;

	while (1) {
		cnt = 0;
		memset(ptr, -1, sizeof ptr);
		for (int i = 1, m; i <= N; ++i) {
			if (songs[i].empty()) continue;
			if (l[i] < r[i]) {
				++cnt;
				m = l[i] + r[i] >> 1;
				np[i] = ptr[m]; ptr[m] = i;
			}
		}
		if (!cnt) break;

		memset(seg_tree, 0, sizeof seg_tree);
		for (int m = 0, i, s, e; m < hi; ++m) {
			i = dptr[m];
			while (~i) {
				s = in[data[i].p], e = out[data[i].p];
				update(s, e, data[i].s / (e - s + 1));
				i = nd[i];
			}
			i = ptr[m];
			while (~i) {
				ll score = 0;
				for (const int& song : songs[i])
					score += get(in[song]);
				if (score > J * songs[i].size()) r[i] = m;
				else l[i] = m + 1;
				i = np[i];
			}
		}
	}
	for (int i = 1; i <= N; ++i)
		std::cout << t[r[singer[i]]] << '\n';
}