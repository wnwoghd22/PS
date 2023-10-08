#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1001;
const ll INF = 1e17;

ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
struct Fraction {
	ll num, den;
	Fraction(ll n, ll d) : num(n), den(d) { if (den < 0) num *= -1, den *= -1; if (!num) den = 1; }
	Fraction(const Fraction& f) : num(f.num), den(f.den) {}
	Fraction& operator=(const Fraction& f) { if (this != &f) num = f.num, den = f.den; return *this; }
	Fraction normalize() const { ll g = gcd(std::abs(num), den); return Fraction(num / g, den / g); }
	Fraction inv() const { return Fraction(den, num); }
	Fraction operator+(const Fraction& r) const {
		ll d = den * r.den / gcd(den, r.den);
		ll n = num * d / den + r.num * d / r.den;
		return Fraction(n, d).normalize();
	}
	Fraction operator-() const { return Fraction(-num, den); }
	Fraction operator-(const Fraction& r) const { return *this + (-r); }
	Fraction operator*(const Fraction& r) const { return Fraction(num * r.num, den * r.den).normalize(); }
	Fraction operator/(const Fraction& r) const { return *this * r.inv(); }
	bool operator<(const Fraction& r) const { return num * r.den < r.num * den; }
	bool operator==(const Fraction& r) const { return num * r.den == r.num * den; }
	friend std::ostream& operator<<(std::ostream& o, const Fraction& f) { return (o << f.num << '/' << f.den); }
};

struct Slope {
	int u, v;
	Fraction f;
	Slope() : u(-1), v(-1), f(0, 1) {}
	Slope(int u, int v, const Fraction& f) : u(u), v(v), f(f.normalize()) {}
	bool operator<(const Slope& r) const { return f < r.f; }
} slopes[LEN * LEN];
int M;

struct Pos { 
	ll x, y; 
	int i;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
} pos[LEN];
int N, idx[LEN], val[LEN], ret;
char c;

struct LenNode {
	int max, lm, rm, full;
	LenNode operator+(const LenNode& r) const {
		return {
			std::max({ max, r.max, rm + r.lm }),
			full ? max + r.lm : lm,
			r.full ? rm + r.max : r.rm,
			full & r.full
		};
	}
} seg_len[LEN * 4];
void update_len(int x, int d, int s = 0, int e = N - 1, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_len[i] = { d, d, d, d };
		return;
	}
	int m = s + e >> 1;
	update_len(x, d, s, m, i << 1);
	update_len(x, d, m + 1, e, i << 1 | 1);
	seg_len[i] = seg_len[i << 1] + seg_len[i << 1 | 1];
}
LenNode get_len(int l, int r, int s = 0, int e = N - 1, int i = 1) {
	if (e < l || r < s) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return seg_len[i];
	int m = s + e >> 1;
	return get_len(l, r, s, m, i << 1) + get_len(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i].x >> pos[i].y >> c;
		pos[i].i = i;
		val[i] = c == 'R';
	}
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			int dx = pos[i].x - pos[j].x;
			int dy = pos[i].y - pos[j].y;
			if (!dx) continue;
			slopes[M++] = { i, j, Fraction(dy, dx) };
		}
	}
	std::sort(pos, pos + N);
	std::sort(slopes, slopes + M);
	for (int i = 0; i < N; ++i) {
		idx[pos[i].i] = i;
		update_len(i, val[pos[i].i]);
	}
	ret = std::max(ret, seg_len[1].max);

	for (int i = 0, j; i < M; i = j) {
		j = i;
		while (j < M && slopes[i].f == slopes[j].f) {
			int u = slopes[j].u, v = slopes[j].v;
			int x = idx[u], y = idx[v];
			int v0 = val[u], v1 = val[v];

			update_len(x, v1), update_len(y, v0);
			idx[u] = y, idx[v] = x;
			++j;
		}
		ret = std::max(ret, seg_len[1].max);
	}
	std::cout << ret;
}