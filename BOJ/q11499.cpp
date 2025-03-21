#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;

struct Q {
	int k, d;
	bool operator<(const Q& o) const {
		return k == o.k ? d > o.d : k > o.k;
	}
} q[LEN];

struct Pos {
	int x, y;
} pos[LEN];
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (ll)(d2.x - d1.x) * (d3.y - d2.y) - (ll)(d2.y - d1.y) * (d3.x - d2.x);
}
ld euc(const Pos& p1, const Pos& p2) {
	return sqrt((ll)(p1.x - p2.x) * (p1.x - p2.x) + (ll)(p1.y - p2.y) * (p1.y - p2.y));
}

int T, N, M, st[LEN], sp;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	(std::cout << std::fixed).precision(7);
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y;
		std::cin >> M;
		for (int i = 0; i < M; ++i) std::cin >> q[i].k >> q[i].d;
		std::sort(q, q + M);

		ld ret = 0;
		ld cur = 0;
		int sp = 1;
		for (int k = N - 1, j = 0, i, dx, dy; k >= 0; --k) {
			i = (k + 1) % N;
			dx = pos[i].x - pos[k].x;
			dy = pos[i].y - pos[k].y;
			if (dx) dx /= std::abs(dx);
			if (dy) dy /= std::abs(dy);
			while (j < M && q[j].k == k) {
				Pos p = { pos[k].x + dx * q[j].d, pos[k].y + dy * q[j].d };
				while (sp > 1 && cross(pos[st[sp - 2]], pos[st[sp - 1]], p) <= 0) {
					cur -= euc(pos[st[sp - 2]], pos[st[sp - 1]]);
					sp--;
				}
				ret += cur + euc(pos[st[sp - 1]], p);
				++j;
			}
			while (sp > 1 && cross(pos[st[sp - 2]], pos[st[sp - 1]], pos[k]) <= 0) {
				cur -= euc(pos[st[sp - 2]], pos[st[sp - 1]]);
				sp--;
			}
			st[sp++] = k; 
			cur += euc(pos[st[sp - 2]], pos[st[sp - 1]]);
		}
		std::cout << ret << '\n';
	}
}