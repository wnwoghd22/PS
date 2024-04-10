#include <iostream>
#include <vector>

typedef long long ll;
const ll MOD = 1e9 + 7;
const int LEN = 5e4;

struct Pos { ll x, y; };
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x); }
ll dot(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.x - d2.x) + (d2.y - d1.y) * (d3.y - d2.y); }
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
	ll c = cross(d1, d2, d3);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
bool intersect(const Pos& d1, const Pos& d2, const Pos& d3) { return !ccw(d1, d2, d3) && dot(d1, d3, d2) >= 0; }

std::vector<Pos> hull;
ll S[LEN];
int N, M, ret[2];

int check(const std::vector<Pos>& hull, const Pos& p) {
	int l = 1, r = N - 1, m, x;
	if (ccw(hull[0], hull[l], p) <= 0) return -1 * !intersect(hull[0], hull[l], p);
	if (ccw(hull[0], hull[r], p) >= 0) return -1 * !intersect(hull[0], hull[r], p);
	while (l < r - 1) {
		m = l + r >> 1;
		x = ccw(hull[0], hull[m], p);
		if (x >= 0) l = m;
		else r = m;
	}
	x = ccw(hull[l], hull[r], p);
	if (x > 0) return x;
	return -1 * !intersect(hull[l], hull[r], p);
}

// thank you brother
ll get_area(const std::vector<Pos>& hull, const Pos& p) {
	int l = 0, r = 0;
	int ccw1 = ccw(p, hull[0], hull[1]), ccwN = ccw(p, hull[0], hull[N - 1]);

	if (ccw1 * ccwN >= 0) {
		if (!ccw1 && dot(p, hull[1], hull[0]) > 0) l = 1;
		if (!ccwN && dot(p, hull[N - 1], hull[0]) > 0) l = N - 1;
		int s = 0 + !ccw1, e = N - 1 - !ccwN, m;
		bool f = ccw(p, hull[s], hull[s + 1]) >= 0;
		while (s < e) {
			m = s + e >> 1;
			Pos pp = p, cur = hull[m], nxt = hull[(m + 1) % N];
			if (!f) std::swap(pp, cur);
			if (ccw(pp, cur, nxt) > 0) s = m + 1;
			else e = m;
		}
		r = s;
		if (!ccw(p, hull[r], hull[r + 1]) && dot(p, hull[r + 1], hull[r]) > 0) r = (r + 1) % N;
	}
	else {
		int s = 0, e = N - 1, m, x;
		bool f = ccw1 > 0 && ccwN < 0;
		while (s < e - 1) {
			m = s + e >> 1;
			x = ccw(hull[0], hull[m], p);
			if (!f) x *= -1;
			if (x > 0) s = m;
			else e = m;
		}
		int s1 = 0, e1 = s;
		while (s1 < e1) {
			m = s1 + e1 >> 1;
			Pos pp = p, cur = hull[m], nxt = hull[(m + 1) % N];
			if (!f) std::swap(pp, cur);
			if (ccw(pp, cur, nxt) > 0) s1 = m + 1;
			else e1 = m;
		}
		l = s1;
		if (!ccw(p, hull[l], hull[(l + 1) % N]) && dot(p, hull[(l + 1) % N], hull[l]) > 0) l = (l + 1) % N;

		int s2 = e, e2 = N - 1;
		while (s2 < e2) {
			m = s2 + e2 >> 1;
			Pos pp = p, cur = hull[m], nxt = hull[(m + 1) % N];
			if (!f) std::swap(pp, cur);
			if (ccw(pp, cur, nxt) < 0) s2 = m + 1;
			else e2 = m;
		}
		r = s2;
		if (!ccw(p, hull[r], hull[(r + 1) % N]) && dot(p, hull[(r + 1) % N], hull[r]) > 0) r = (r + 1) % N;
	}
	
	if (l > r) std::swap(l, r);
	ll area = S[r] - S[l] - cross(hull[0], hull[l], hull[r]);
	return std::min(area, S[N - 1] - area);
}


int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, x, y; i < N; ++i) {
		std::cin >> x >> y;
		hull.push_back({ x, y });
	}
	for (int i = 2; i < N; ++i) {
		S[i] = cross(hull[0], hull[i - 1], hull[i]);
		S[i] = S[i] + S[i - 1];
	}

	for (int k = 0; k < 2; ++k) {
		for (int i = 0, x, y; i < M; ++i) {
			std::cin >> x >> y;
			int f = check(hull, { x, y });
			if (f > 0) ret[k] = (ret[k] + S[N - 1]) % MOD;
			if (f < 0) ret[k] = (ret[k] + get_area(hull, { x, y })) % MOD;
		}
	}

	if (ret[0] == ret[1]) std::cout << "same\n";
	else if (ret[0] > ret[1]) std::cout << "ym\n";
	else std::cout << "hb\n";
	std::cout << ret[0] << ' ' << ret[1];
}