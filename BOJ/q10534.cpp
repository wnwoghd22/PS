#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 50'001;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

struct Seg {
	int h, l, r, i;
	bool operator<(const Seg& o) const {
		return h == o.h ? l == o.l ? r < o.r : l < o.l : h < o.h;
	}
} E[2][LEN * 2];
int N, S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	int ret = 0;
	for (int i = 0, x, y, h, w; i < N; ++i) {
		std::cin >> x >> y >> w >> h;
		ret = std::max(ret, S[i] = w * h);
		E[0][i * 2] = { x + w, y, y + h, i };
		E[0][i * 2 + 1] = { x, y, y + h, i };
		E[1][i * 2] = { y + h, x, x + w, i };
		E[1][i * 2 + 1] = { y, x, x + w, i };
	}
	memset(p, -1, sizeof p);
	for (int k = 0, h, r, i; k < 2; ++k) {
		std::sort(E[k], E[k] + N * 2);
		h = E[k][0].h;
		r = E[k][0].r;
		i = E[k][0].i;
		for (int j = 1; j < N * 2; ++j) {
			if (h != E[k][j].h) {
				h = E[k][j].h;
				r = E[k][j].r;
				i = E[k][j].i;
				continue;
			}
			if (E[k][j].l <= r) {
				int a = find(i), b = find(E[k][j].i);
				if (join(a, b)) {
					S[a] = S[b] = S[a] + S[b];
					ret = std::max(ret, S[a]);
				}
			}
			if (E[k][j].r > r) {
				r = E[k][j].r;
				i = E[k][j].i;
			}
		}
	}
	std::cout << ret;
}