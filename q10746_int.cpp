#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'000;
const int BF_LEN = 300;
const ll INF = 1e9 + 7;
int N, K, Q;
ll maxX = -INF, maxY = -INF, minX = INF, minY = INF;

struct Pos {
	ll x, y;
	int i;
	bool operator<(const Pos& p) const { return x == p.x ? y < p.y : x < p.x; }
} sorted[LEN << 1], P;
int bp, up, lp, buffer[LEN], pos[LEN << 1], upper[LEN << 1], lower[LEN << 1], order[LEN + 1];

ll cross(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x);
}
ll dot(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (d2.x - d1.x) * (d3.x - d2.x) + (d2.y - d1.y) * (d3.y - d2.y);
}
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
	ll c = cross(d1, d2, d3);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
void lower_hull() { //lower monotone chain
	lp = 0;
	if (K <= 2) {
		for (int i = 0; i < K; ++i) lower[lp++] = pos[i];
		return;
	}
	for (int i = 0; i < K; ++i) {
		while (lp > 1 && cross(sorted[lower[lp - 2]], sorted[lower[lp - 1]], sorted[pos[i]]) <= 0) --lp;
		lower[lp++] = pos[i];
	}
}
void upper_hull() { //lower monotone chain
	up = 0;
	if (K <= 2) {
		for (int i = K - 1; i >= 0; --i) upper[up++] = pos[i];
		return;
	}
	for (int i = K - 1; i >= 0; --i) {
		while (up > 1 && cross(sorted[upper[up - 2]], sorted[upper[up - 1]], sorted[pos[i]]) <= 0) --up;
		upper[up++] = pos[i];
	}
}

int binary_search_lower(ll A, ll B, ll C) {
	int l = 0, r = lp - 1, m, ret = r;
	ll S = A * sorted[lower[l]].x + B * sorted[lower[l]].y - C;
	ll E = A * sorted[lower[r]].x + B * sorted[lower[r]].y - C;
	if (!S || !E || (S > 0) != (E > 0)) return 0; // crossing
	if (S < 0) return -1; // below line
	r--;
	while (l <= r) {
		m = l + r >> 1;
		ll dx = sorted[lower[m + 1]].x - sorted[lower[m]].x;
		ll dy = sorted[lower[m + 1]].y - sorted[lower[m]].y;
		if (dy * B >= -dx * A) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return A * sorted[lower[ret]].x + B * sorted[lower[ret]].y - C > 0;
}

int binary_search_upper(ll A, ll B, ll C) {
	int l = 0, r = up - 1, m, ret = r;
	ll S = A * sorted[upper[l]].x + B * sorted[upper[l]].y - C;
	ll E = A * sorted[upper[r]].x + B * sorted[upper[r]].y - C;
	if (!S || !E || (S > 0) != (E > 0)) return 0; // crossing
	if (S > 0) return 1; // above line
	r--;
	while (l <= r) {
		m = l + r >> 1;
		ll dx = sorted[upper[m]].x - sorted[upper[m + 1]].x;
		ll dy = sorted[upper[m]].y - sorted[upper[m + 1]].y;
		if (dy * B >= -dx * A) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return -(A * sorted[upper[ret]].x + B * sorted[upper[ret]].y - C < 0);
}

struct Query {
	ll A, B, C;
	int i;
} queries[LEN];
int qp;

void init(int cur) {
	K = 0;
	for (int i = 0; i < N; ++i)
		if (sorted[i].i <= cur) pos[K++] = i;
	lower_hull(); upper_hull();
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin >> N >> Q;
	for (int i = 0; i < N; ++i) {
		std::cin >> sorted[i].x >> sorted[i].y;
		maxX = std::max(maxX, sorted[i].x);
		maxY = std::max(maxY, sorted[i].y);
		minX = std::min(minX, sorted[i].x);
		minY = std::min(minY, sorted[i].y);
		sorted[i].i = 0;
	}
	for (int i = 1, q; i <= Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> sorted[N].x >> sorted[N].y;
			sorted[N].i = i;
			++N;
		}
		if (q == 2) {
			std::cin >> queries[qp].A >> queries[qp].B >> queries[qp].C;
			queries[qp].i = i;
			++qp;
		}
	}
	std::sort(sorted, sorted + N);
	for (int i = 0; i < N; ++i) order[sorted[i].i] = i;
	init(0);
	for (int i = 0, j = 1, k; i < qp; ++i) {
		while (j < queries[i].i) {
			if (order[j]) {
				k = order[j];
				buffer[bp++] = k;
				maxX = std::max(maxX, sorted[k].x);
				maxY = std::max(maxY, sorted[k].y);
				minX = std::min(minX, sorted[k].x);
				minY = std::min(minY, sorted[k].y);
			}
			++j;
		}
		if (bp > BF_LEN) init(queries[i].i), bp = 0;
		
		ll A = queries[i].A;
		ll B = queries[i].B;
		ll C = queries[i].C;
		bool flag = 0;

		if (!A) { // horizontal
			if ((B * maxY == C) ||
				(B * minY == C) ||
				(B * maxY > C) != (B * minY > C))
				flag = 1;
		}
		else if (!B) { // vertical
			if ((A * maxX == C) ||
				(A * minX == C) ||
				(A * maxX > C) != (A * minX > C))
				flag = 1;
		}
		else {
			if (B < 0) A *= -1, B *= -1, C *= -1;
			int dir_d = binary_search_lower(A, B, C);
			int dir_u = binary_search_upper(A, B, C);
			if (dir_u * dir_d > 0) {
				for (k = 0; k < bp; ++k) {
					Pos p = sorted[buffer[k]];
					ll cur = A * p.x + B * p.y - C;
					if (dir_d * cur <= 0) {
						flag = 1;
						break;
					}
				}
			}
			else flag = 1;
			// std::cout << dir_d << ' ' << dir_u << ' ';
		}
		std::cout << (flag ? "NO\n" : "YES\n");
	}
}