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
	Fraction& operator=(const Fraction& f) {
		if (this == &f) return *this;
		num = f.num; den = f.den; return *this; 
	}
	const Fraction& normalize() const {
		ll g = gcd(std::abs(num), den);
		std::cout << "gcd: " << num << ' ' << den << ' ' << g << '\n';
		ll n = num / g, d = den / g;
		std::cout << "irr: " << n << ' ' << d << '\n';
		// return Fraction(n, d);
		return Fraction(num / g, den / g);
	}
	const Fraction& inv() const { return Fraction(den, num); }
	const Fraction& operator+(const Fraction& r) const {
		ll d = den * r.den / gcd(den, r.den);
		ll n = num * d / den + r.num * d / r.den;
		Fraction result(n, d);
		Fraction norm = result.normalize();
		return norm;
	}
	const Fraction& operator-() const { return Fraction(-num, den); }
	const Fraction& operator-(const Fraction& r) const { return Fraction(*this) + (-r); }
	const Fraction& operator*(const Fraction& r) const {
		std::cout << *this << " * " << r << '\n';
		Fraction result = Fraction(num * r.num, den * r.den);
		Fraction norm = result.normalize();
		std::cout << result << ", norm: " << norm << '\n';
		return norm;

	}
	const Fraction& operator/(const Fraction & r) const { return Fraction(*this) * r.inv(); }
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
		Fraction l(0, 1), r(0, 1);
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
		Fraction _n(0, 1), _d(0, 1);
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
			std::cout << "MUL: " << f << ' ' << left->val << ' ' << right->val << '\n';
			// std::cout << f * right->val << '\n';
			_n = f * right->val;
			left->dfs_f(_n);
			_n = f * left->val;
			right->dfs_f(_n);
			return;
		case 4:
			std::cout << "DIV: " << f << ' ' << left->val << ' ' << right->val << '\n';
			_n = f / right->val;
			left->dfs_f(_n);
			_n = f * left->val;
			_d = right->val * right->val;
			std::cout << "NUM/DEN: " << _n << " / " << _d << '\n';
			right->dfs_f(-(_n / _d));
			return;
		default:
			return;
		}
	}
} *tree[LEN];
std::string A, B, S[LEN];
char op;
int idx, N;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0, f = 0; i < N; ++i) {
		std::cin >> S[i] >> op;
		if (map.find(S[i]) == map.end()) {
			map[S[i]] = idx++;
			tree[map[S[i]]] = new Node;
		}
		if (op == 'E') { // leaf
			std::cin >> f;
			tree[map[S[i]]]->op = 0;
			tree[map[S[i]]]->val = Fraction(f, 1);
		}
		else {
			std::cin >> A >> B;
			if (map.find(A) == map.end()) {
				map[A] = idx++;
				tree[map[A]] = new Node;
			}
			if (map.find(B) == map.end()) {
				map[B] = idx++;
				tree[map[B]] = new Node;
			}
			tree[map[S[i]]]->left = tree[map[A]];
			tree[map[S[i]]]->right = tree[map[B]];
			if (op == 'A') f = 1;
			if (op == 'S') f = 2;
			if (op == 'M') f = 3;
			if (op == 'D') f = 4;
			tree[map[S[i]]]->op = f;
		}
	}
	tree[map["HAPPY"]]->dfs();
	tree[map["HAPPY"]]->dfs_f(Fraction(1, 1));
	std::sort(S, S + N);
	for (int i = 0; i < N; ++i)
		std::cout << S[i] << ' ' << tree[map[S[i]]]->val << ' ' << tree[map[S[i]]]->f << '\n';
		// std::cout << S[i] << ' ' << tree[map[S[i]]]->f << '\n';
}