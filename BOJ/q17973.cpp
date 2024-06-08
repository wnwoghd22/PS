#include <iostream>
#include <algorithm>
#include <cassert>

typedef long long ll;
const int LEN = 1001;
const ll INF = 1e17;

struct Pos {
	int x, y;
	bool operator<(const Pos& o) const {
		return x == o.x ? y < o.y : x < o.x;
	}
} p[LEN];
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (ll)(p2.x - p1.x) * (p3.y - p2.y) - (ll)(p2.y - p1.y) * (p3.x - p2.x); }

struct Slope {
	int u, v;
	ll dx() const { return p[v].x - p[u].x; }
	ll dy() const { return p[v].y - p[u].y; }
	bool operator<(const Slope& o) const {
		return dy() * o.dx() < o.dy() * dx();
	}
} slopes[LEN * LEN];

int N, o[LEN], idx[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	std::sort(p, p + N);

	int len = 0;
	for (int u = 0; u < N; ++u) {
		o[u] = idx[u] = u;
		for (int v = u + 1; v < N; ++v) {
			if (p[u].x <= p[v].x) slopes[len++] = { u, v };
			else slopes[len++] = { v, u };
		}
	}
	std::sort(slopes, slopes + len);

	ll alpha = INF;
	ll cnt = 0;
	ll d = 0;
	for (int i = 0, u, v; i < len; ++i) {
		int ou = o[u = slopes[i].u];
		int ov = o[v = slopes[i].v];
		assert(std::abs(ou - ov) == 1);

		std::swap(o[u], o[v]);
		std::swap(idx[ou], idx[ov]);
		if (ou > ov) std::swap(ou, ov);

		d += (ll)ou * (N - ov - 1);
		for (int x = std::max(0, ou - 2); x < ou; ++x) {
			for (int y = std::min(N - 1, ov + 2); y > ov; --y) {
				ll area = std::abs(cross(p[u], p[v], p[idx[x]])) + std::abs(cross(p[u], p[v], p[idx[y]]));

				if (area < alpha) {
					cnt = 0;
					alpha = area;
				}
				if (area == alpha) {
					cnt++;
					if (cross(p[idx[x]], p[idx[y]], p[u]) > 0 == cross(p[idx[x]], p[idx[y]], p[v]) > 0) cnt++;
				}

			}
		}
	}
	std::cout << d << ' ' << cnt << '\n';
	std::cout << d + cnt;
}