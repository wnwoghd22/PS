#include <iostream>
#include <vector>

typedef long long ll;
const ll MOD = 1e9 + 7;
const int LEN = 5e4;

struct Pos { ll x, y; };
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x); }
ll dot(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) + (d2.y - d1.y) * (d3.x - d2.x); }
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
	ll c = cross(d1, d2, d3);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
bool intersect(const Pos& d1, const Pos& d2, const Pos& d3) { return !ccw(d1, d2, d3) && dot(d1, d3, d2); }

std::vector<Pos> hull;
ll S[LEN];
int N, M, ret[2];

int check(const std::vector<Pos>& hull, const Pos& p) {
	int l = 1, r = N - 1, m, x;
	if (ccw(hull[0], hull[l], p) >= 0) return -1 * !intersect(hull[0], hull[l], p);
	if (ccw(hull[r], hull[0], p) >= 0) return -1 * !intersect(hull[r], hull[0], p);
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

ll get_area(const const std::vector<Pos>& hull, const Pos& p) {
	int l = 0, r = 0;


	
	if (l > r) std::swap(l, r);
	return (S[r] - S[l] - cross(hull[0], hull[l], hull[r])) % MOD;
}


int main() {
	std::cin >> N >> M;
	for (int i = 0, x, y; i < N; ++i) {
		std::cin >> x >> y;
		hull.push_back({ x, y });
	}
	for (int i = 2; i < N; ++i) {
		S[i] = cross(hull[0], hull[i - 1], hull[i]);
		S[i] = S[i] + S[i - 1] % MOD;
	}

	for (int k = 0; k < 2; ++k) {
		for (int i = 0, x, y; i < M; ++i) {
			std::cin >> x >> y;
			int f = check(hull, { x, y });
			if (f > 0) ret[i] = (ret[i] + S[N - 1]) % MOD;
			if (f < 0) ret[i] = (ret[i] + get_area(hull, { x, y })) % MOD;
		}
	}

}