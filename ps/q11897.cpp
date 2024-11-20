#include <iostream>
#include <cstring>

const int V_LEN = 701;
const int E_LEN = 123456;

int V, E, Q;
int u[E_LEN], v[E_LEN];
int L[V_LEN], R[V_LEN];
int p[V_LEN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int query(int l, int r) {
	int ret = V;
	memset(p, -1, sizeof p);
	for (int i = 0; L[i] < l; ++i)
		if (join(u[L[i]], v[L[i]])) --ret;
	for (int i = 0; R[i] > r; ++i)
		if (join(u[R[i]], v[R[i]])) --ret;
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> V >> E;
	memset(p, -1, sizeof p);
	for (int i = 0, j = 0; i < E; ++i) {
		std::cin >> u[i] >> v[i];
		if (join(u[i], v[i])) L[j++] = i;
	}
	memset(p, -1, sizeof p);
	for (int i = E - 1, j = 0; i >= 0; --i) {
		if (join(u[i], v[i])) R[j++] = i;
	}
	std::cin >> Q;
	for (int q = 0, l, r; q < Q; ++q) {
		std::cin >> l >> r;
		std::cout << query(l - 1, r - 1) << '\n';
	}
}