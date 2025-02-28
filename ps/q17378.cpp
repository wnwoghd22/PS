#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 300'001;
const ll MOD = 1e9 + 7;

ll p(ll x, ll k) {
	ll ret = 1;
	while (k) {
		if (k & 1) ret = ret * x % MOD;
		x = x * x % MOD;
		k >>= 1;
	}
	return ret;
}
struct Fraction {
	ll num, den;
	static ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
	Fraction(ll n = 0, ll d = 1) : num(n), den(d) { if (den < 0) num *= -1, den *= -1; if (!num) den = 1; }
	Fraction(const Fraction& f) : num(f.num), den(f.den) {}
	Fraction& operator=(const Fraction& f) { if (this != &f) num = f.num, den = f.den; return *this; }
	Fraction normalize() const { ll g = gcd(std::abs(num), den); return Fraction(num / g, den / g); }
	Fraction inv() const { return Fraction(den, num); }
	ll mod() const { return (num + MOD * MOD) % MOD * p(den, MOD - 2) % MOD; }
	Fraction operator+(const Fraction& r) const {
		ll d = den * r.den / gcd(den, r.den);
		ll n = num * d / den + r.num * d / r.den;
		return Fraction(n, d).normalize();
	}
	Fraction operator-() const { return Fraction(-num, den); }
	Fraction operator-(const Fraction& r) const { return *this + (-r); }
	Fraction operator*(const Fraction& r) const { return Fraction(num * r.num, den * r.den).normalize(); }
	Fraction operator/(const Fraction& r) const { return *this * r.inv(); }
	bool operator<(const Fraction& o) const { return num * o.den < o.num * den; }
	bool operator<=(const Fraction& o) const { return num * o.den <= o.num * den; }
	bool operator>(const Fraction& o) const { return o < *this; }
	friend std::ostream& operator<<(std::ostream& o, const Fraction& f) { return (o << f.num << '/' << f.den); }
};

int N, st[LEN];

struct Circle {
	ll x, r;
	Fraction s, e;
	ll hemi(ll k) const {
		static const ll inv3 = p(3, MOD - 2);
		return (r * r % MOD * k % MOD - inv3 * p(k, 3) % MOD + MOD * MOD) % MOD;
	}
	ll volume() const {
		ll ret = 0;
		ret += hemi(x - s.mod());
		ret += hemi(e.mod() - x);
		return (ret + MOD * MOD) % MOD;
	}
	ll L() const { return x - r; }
	ll R() const { return x + r; }
	bool operator<(const Circle& o) const { return x == o.x ? r < o.r : x < o.x; }
} C[LEN];

Fraction intersect(const ll& x1, const ll& r1, const ll& x2, const ll& r2) {
	return Fraction(r2 * r2 - x2 * x2 - r1 * r1 + x1 * x1, -2 * x2 + 2 * x1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> C[i].x >> C[i].r;
	std::sort(C, C + N);

	ll S = 0;
	for (int i = 0, sp = 0, j; i < N; ++i) {
		C[i].s = C[i].x - C[i].r;
		C[i].e = C[i].x + C[i].r;
		while (sp) {
			j = st[sp - 1];
			if (C[j].e < C[i].s) break;
			if (C[j].L() <= C[i].L() && C[i].R() <= C[j].R()) {
				std::swap(C[i].s, C[i].e);
				break;
			}
			if (C[i].L() <= C[j].L() && C[j].R() <= C[i].R()) {
				S = (S - C[j].volume() + MOD) % MOD;
				--sp;
				continue;
			}
			Fraction k = intersect(C[j].x, C[j].r, C[i].x, C[i].r);
			if (k <= C[j].s) {
				S = (S - C[j].volume() + MOD) % MOD;
				--sp;
				continue;
			}
			else {
				S = (S - C[j].volume() + MOD) % MOD;
				C[j].e = k; C[i].s = k;
				S = (S + C[j].volume()) % MOD;
				break;
			}
		}
		if (C[i].s < C[i].e) {
			st[sp++] = i;
			S = (S + C[i].volume()) % MOD;
		}
	}
	std::cout << S;
}
