#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;

int N, M, A[LEN], c[LEN], o[LEN]; // compressed, order

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) c[k++] = A[o[i]] <= A[o[j]] ? o[i++] : o[j++];
	while (i <= m) c[k++] = o[i++];
	while (j <= r) c[k++] = o[j++];
	for (i = l; i <= r; ++i) o[i] = c[i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

struct Node {
	int l, r, v;
} seg_tree[LEN << 5];

int cur = 0, ptr[LEN];
void init(int i, int s, int e) {
	if (s == e) return;
	int m = s + e >> 1;
	seg_tree[i].l = ++cur; seg_tree[i].r = ++cur;
	init(seg_tree[i].l, s, m); init(seg_tree[i].r, m + 1, e);
}
void update(int p, int i, int s, int e, int x, int d) {
	if (s == e) { seg_tree[i].v += d; return; }
	int m = s + e >> 1;
	if (x <= m) { // update left
		seg_tree[i].l = ++cur; seg_tree[i].r = seg_tree[p].r;
		update(seg_tree[p].l, seg_tree[i].l, s, m, x, d);
	}
	else {
		seg_tree[i].r = ++cur; seg_tree[i].l = seg_tree[p].l;
		update(seg_tree[p].r, seg_tree[i].r, m + 1, e, x, d);
	}
	seg_tree[i].v = seg_tree[seg_tree[i].l].v + seg_tree[seg_tree[i].r].v;
}

int query(int x, int y, int l, int p, int s, int e, int k) {
	if (s == e) return s;
	Node& nx = seg_tree[x];
	Node& ny = seg_tree[y];
	Node& nl = seg_tree[l];
	Node& np = seg_tree[p];
	int m = s + e >> 1;
	int d = seg_tree[nx.l].v + seg_tree[ny.l].v - seg_tree[nl.l].v - seg_tree[np.l].v;
	if (d >= k) return query(nx.l, ny.l, nl.l, np.l, s, m, k);
	else return query(nx.r, ny.r, nl.r, np.r, m + 1, e, k - d);
}

std::vector<int> graph[LEN];
int level[LEN], parent[LEN][21];

void dfs(int u, int p = 0) {
	parent[u][0] = p;
	level[u] = level[p] + 1;
	for (int i = 1, v = p; v; v = parent[u][i++]) 
		parent[u][i] = parent[v][i - 1];
	update(ptr[p], ptr[u] = ++cur, 1, N, c[u], 1);
	for (const int& v : graph[u]) {
		if (v == p) continue;
		dfs(v, u);
	}
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
int query(int x, int y, int k) {
	int l = lca(x, y);
	int p = parent[l][0];
	return query(ptr[x], ptr[y], ptr[l], ptr[p], 1, N, k);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) std::cin >> A[i], o[i] = i;
	for (int i = 1, x, y; i < N; ++i) {
		std::cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	merge_sort(1, N);
	for (int i = 1; i <= N; ++i) c[o[i]] = i;
	// for (int i = 0; i < N; ++i) std::cout << o[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << c[i] << ' '; std::cout << '\n';

	init(0, 1, N);
	dfs(1);

	for (int m = 0, x, y, k; m < M; ++m) {
		std::cin >> x >> y >> k;
		std::cout << A[o[query(x, y, k)]] << '\n';
	}
}