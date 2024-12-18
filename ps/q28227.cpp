#include <iostream>
#include <cmath>

typedef long long ll;
typedef long double ld;
const int LEN = 200'001;
const ld PI = 3.1415926535;

ld intersect(const ll& x1, const ll& r1, const ll& x2, const ll& r2) {
	if (x2 - r2 < x1 - r1) return x2 - r2;
	return (r2 * r2 - x2 * x2 - r1 * r1 + x1 * x1) / (ld)(-2 * x2 + 2 * x1);
}

int N, X[LEN], R[LEN], st[LEN];
ld S[LEN], l[LEN], r[LEN];

ld f(ld c, ld x, ld r) {
	ld y = sqrt(r * r - (x - c) * (x - c));
	ld fan = r * r * acos(y / r) / 2;
	ld tri = (c - x) * y / 2;
	return fan + tri;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	(std::cout << std::fixed).precision(9);
	std::cin >> N;
	for (int i = 0, sp = 0, j; i < N; ++i) {
		std::cin >> X[i] >> R[i];
		l[i] = X[i] - R[i]; r[i] = X[i];
		while (sp) {
			j = st[sp - 1];
			if (X[j] <= X[i] - R[i]) break;
			if ((ll)R[i] * R[i] - (ll)(X[i] - X[j]) * (X[i] - X[j]) <= (ll)R[j] * R[j]) {
				S[i] += S[j];
				l[i] = X[j];
				break;
			}
			if ((l[i] = intersect(X[j], R[j], X[i], R[i])) > l[j]) {
				S[i] += (S[j] -= f(X[j], l[i], R[j]) - f(X[j], r[j], R[j]));
				r[j] = l[i];
				break;
			}	
			--sp;
		}
		st[sp++] = i;
		S[i] += f(X[i], l[i], R[i]);
		std::cout << S[i] << '\n';
	}
}
