#include <iostream>
#include <cstring>

const int V_LEN = 702;
const int E_LEN = 123460;

int V, E, Q;
int u[E_LEN], v[E_LEN];
int pre[E_LEN], nxt[E_LEN];
int L[V_LEN], R[V_LEN];
int p[V_LEN];
int c[V_LEN][V_LEN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> V >> E;
	memset(p, -1, sizeof p);
	for (int i = 1; i <= E; ++i) {
		std::cin >> u[i] >> v[i];
		pre[i] = pre[i - 1];
		if (join(u[i], v[i])) L[pre[i]++] = i;
	}
	memset(p, -1, sizeof p);
	for (int i = E; i > 0; --i) {
		nxt[i] = nxt[i + 1];
		if (join(u[i], v[i])) R[nxt[i]++] = i;
	}
	for (int i = 0; i <= pre[E]; ++i) {
		memset(p, -1, sizeof p);
		c[i][0] = i;
		for (int j = 0; j < i; ++j) join(u[L[j]], v[L[j]]);
		for (int j = 0; j < pre[E]; ++j) {
			if (join(u[R[j]], v[R[j]])) c[i][j + 1]++;
			c[i][j + 1] += c[i][j];
		}
	}

	std::cin >> Q;
	for (int q = 0, l, r; q < Q; ++q) {
		std::cin >> l >> r;
		l = pre[l - 1], r = nxt[r + 1];
		std::cout << V - c[l][r] << '\n';
	}
}