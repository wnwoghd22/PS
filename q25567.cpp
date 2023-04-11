#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;
const int LEN = 200'001;

int N, L, Q;
int _i[LEN], _j[LEN];
ll S[LEN]; int sp, st[LEN];
int p[LEN]; ll w[LEN], t[LEN];

struct Info { int i; ll w; };
Info find(int i) {
	if (p[i] < 0) return { i, 0 };
	Info q = find(p[i]);
	p[i] = q.i;
	w[i] += q.w;
	return { p[i], w[i] };
}

bool join(int a, int b) {
	a = _i[a], b = _i[b];
	Info _a = find(a), _b = find(b);
	if (_a.i == _b.i) return false;
	p[_a.i] += p[_b.i]; p[_b.i] = _a.i;
	w[_b.i] += t[_a.i]; t[_a.i] += t[_b.i];
	return true;
}

ll get_sum(int x) {
	int i = _i[x], j = _j[x];
	ll sum = find(i).w;
	// std::cout << "pivot sum: " << sum << '\n';
	return sum + S[st[i] + j];
}

int main() {
	freopen("input.txt", "r", stdin);
	memset(p, -1, sizeof p);
	std::cin >> N;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> L;
		std::cin >> a;
		_i[a] = i; _j[a] = 0;
		st[i] = sp; S[sp++] = a;
		for (int j = 1; j < L; ++j, ++sp) {
			std::cin >> a;
			_i[a] = i; _j[a] = j;
			S[sp] = a + S[sp - 1];
		}
		t[i] = S[sp - 1];
	}
	std::cin >> Q;
	for (int i = 0, q, a, b; i < Q; ++i) {
		std::cin >> q >> a >> b;
		if (q == 1) std::cout << (join(a, b) ? "YES\n" : "NO\n");
		if (q == 2) {
			Info ia = find(_i[a]), ib = find(_i[b]);
			if (ia.i != ib.i) std::cout << -1 << '\n';
			else {
				ll Sa = get_sum(a), Sb = get_sum(b);
				// std::cout << "Sa: " << Sa << ", Sb: " << Sb << ' ';
				if (Sa > Sb) std::cout << Sa - Sb + b << '\n';
				else std::cout << Sb - Sa + a << '\n';
			}
		}
	}
}