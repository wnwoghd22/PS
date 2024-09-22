#include <iostream>
#include <queue>
#include <map>

typedef long long ll;
const int LEN = 40'000;

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
	friend std::ostream& operator<<(std::ostream& o, const Fraction& f) { return (o << f.num << '/' << f.den); }
};

struct Pos {
	Fraction x, y;

};

int p[101];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	p[a] += p[b]; p[b] = a;
	return 1;
}

int main() {

}