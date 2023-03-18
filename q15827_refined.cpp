#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 1000;
std::map<std::string, int> map;
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

struct Node {
	Node* left;
	Node* right;
	Fraction val;
	Fraction f;
	int op;
	Node() : left(0), right(0), val(0, 1), f(0, 1), op(0) {}
	Fraction dfs() {
		switch (op) {
		case 1: return val = left->dfs() + right->dfs();
		case 2: return val = left->dfs() - right->dfs();
		case 3: return val = left->dfs() * right->dfs();
		case 4: return val = left->dfs() / right->dfs();
		default: return val;
		}
	}
	void dfs_f(const Fraction& p) {
		f = p;
		switch (op) {
		case 1:
			left->dfs_f(f);
			right->dfs_f(f);
			return;
		case 2:
			left->dfs_f(f);
			right->dfs_f(-f);
			return;
		case 3:
			left->dfs_f(f * right->val);
			right->dfs_f(f * left->val);
			return;
		case 4:
			left->dfs_f(f / right->val);
			right->dfs_f(-(f * left->val / (right->val * right->val)));
			return;
		default:
			return;
		}
	}
} tree[LEN];
std::string A, B, S[LEN];
char op;
int idx, N;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0, f = 0; i < N; ++i) {
		std::cin >> S[i] >> op;
		if (map.find(S[i]) == map.end()) map[S[i]] = idx++;
		if (op == 'E') { // leaf
			std::cin >> f;
			tree[map[S[i]]].op = 0;
			tree[map[S[i]]].val = Fraction(f, 1);
		}
		else {
			std::cin >> A >> B;
			if (map.find(A) == map.end()) map[A] = idx++;
			if (map.find(B) == map.end()) map[B] = idx++;
			tree[map[S[i]]].left = &tree[map[A]];
			tree[map[S[i]]].right = &tree[map[B]];
			if (op == 'A') f = 1;
			if (op == 'S') f = 2;
			if (op == 'M') f = 3;
			if (op == 'D') f = 4;
			tree[map[S[i]]].op = f;
		}
	}
	tree[map["HAPPY"]].dfs();
	tree[map["HAPPY"]].dfs_f(Fraction(1, 1));
	std::sort(S, S + N);
	for (int i = 0; i < N; ++i)
		std::cout << S[i] << ' ' << tree[map[S[i]]].f << '\n';
}