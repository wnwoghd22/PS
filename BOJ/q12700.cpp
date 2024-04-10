#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1e6 + 1;
typedef unsigned long long ull;

struct BigN {
	ull bit, log, shift;
	BigN(ull n) : bit(n), log(0), shift(0) {
		if (!bit) return;
		for (int i = 0; i < 64; ++i) if (1ll << i & bit) log = i;
		while (~bit & 1) bit >>= 1, --log, ++shift;
	}
	ull msb() const { return log + shift; }
	bool operator==(const BigN& r) const {
		return bit == r.bit && shift == r.shift;
	}
	bool operator<(const BigN& r) const {
		if (msb() == r.msb()) {
			if (log < r.log) return bit << (r.log - log) < r.bit;
			else return bit < r.bit << (log - r.log);
		}
		return msb() < r.msb();
	}
	BigN operator<<(ull i) const { BigN result(*this); if (bit) result.shift += i; return result; }
	BigN operator+(ull k) const {
		BigN result(*this);
		ull diff = k - shift;
		while (diff--) result.bit >>= 1, --result.log, ++result.shift; // result -= result % 2^k
		++result.bit;
		for (int i = 0; i < 64; ++i) if (1ll << i & result.bit) result.log = i;
		while (~result.bit & 1) result.bit >>= 1, --result.log, ++result.shift;
		return result;
	}
	friend std::ostream& operator<<(std::ostream& o, const BigN b) {
		for (int i = b.log; i >= 0; --i) std::cout << !!(b.bit & 1 << i);
		for (int i = 0; i < b.shift; ++i) std::cout << 0;
		return o;
	}
};

class Scale {
	Scale* l;
	Scale* r;
	ull ml, mr; // mass
	ull shift;
public:
	Scale() : l(0), r(0), ml(0), mr(0), shift(0) {}
	Scale(int, int);
	ull dfs() {
		ull ls = l ? l->dfs() : 0;
		ull rs = r ? r->dfs() : 0;
		return shift = std::max(ls, rs) + 1;
	}
	BigN dfs2() {
		BigN ln = l ? l->dfs2() : ml;
		BigN rn = r ? r->dfs2() : mr;
		BigN result = ln < rn ? rn : ln;
		if (result.bit == 0) return result;

		ull lcm = shift - 1;
		// if (!(ln == rn) && result.shift < lcm) result = result + lcm;
		// if (result.shift < lcm) result = result + lcm;
		return result << 1;
	}
} scales[LEN];
Scale::Scale(int l, int r) : l(0), r(0), ml(0), mr(0), shift(0) {
	if (l <= 0) this->ml = -l;
	else this->l = &scales[l];
	if (r <= 0) this->mr = -r;
	else this->r = &scales[r];
}

int main() {
	freopen("input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	int N, L, R;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> L >> R;
		scales[i] = Scale(L, R);
	}
	scales[1].dfs();
	BigN result = scales[1].dfs2();
	std::cout << result;
}