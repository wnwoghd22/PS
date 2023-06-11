#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int V_LEN = 500;
const int E_LEN = 5e6;
const int Q_LEN = 1e5;

int h[V_LEN][V_LEN];
struct Edge {
	int a, b, c;
	bool operator<(const Edge& r) const { return c < r.c; }
} edges[E_LEN];
int ep;

int vp, vptr[E_LEN], cm[E_LEN], vn[E_LEN];

int p[V_LEN * V_LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

int s[Q_LEN], e[Q_LEN], l[Q_LEN], r[Q_LEN];
int qp, qptr[Q_LEN], qi[Q_LEN], qn[Q_LEN];

int N, M, Q, R;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> M >> N >> Q;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> h[i][j];
			if (i > 0) edges[ep++] = { i * N + j, (i - 1) * N + j, std::max(h[i][j], h[i - 1][j]) };
			if (j > 0) edges[ep++] = { i * N + j, i * N + j - 1, std::max(h[i][j], h[i][j - 1]) };

		}
	}
	std::sort(edges, edges + ep);

	memset(vptr, -1, sizeof vptr);
	for (int i = 0, j = -1; i < ep; ++i) {
		if (edges[i].c ^ j)
			j = cm[vp++] = edges[i].c;
		vn[i] = vptr[vp - 1];
		vptr[vp - 1] = i;
	}

	for (int i = 0, x1, y1, x2, y2; i < Q; ++i) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		s[i] = --x1 * N + --y1;
		e[i] = --x2 * N + --y2;
		r[i] = vp;
	}
	while (1) {
		R = qp = 0;
		memset(qptr, -1, sizeof qptr);
		for (int i = 0, m; i < Q; ++i) {
			if (l[i] < r[i]) {
				++R;
				m = l[i] + r[i] >> 1;
				qn[qp] = qptr[m];
				qi[qp] = i;
				qptr[m] = qp++;
			}
		}
		if (!R) break;

		memset(p, -1, sizeof p);
		for (int m = 0; m < vp; ++m) {
			int o = vptr[m];
			while (~o) {
				join(edges[o].a, edges[o].b);
				o = vn[o];
			}
			int q = qptr[m];
			while (~q) {
				int i = qi[q];
				if (find(s[i]) == find(e[i])) r[i] = m;
				else l[i] = m + 1;
				q = qn[q];
			}
		}
	}
	for (int i = 0; i < Q; ++i)
		std::cout << cm[r[i]] << '\n';
}