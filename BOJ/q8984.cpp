#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 1e5;

struct P {
	int t, d;
	bool operator<(const P& r) const {
		return t == r.t ? d < r.d : t < r.t;
	}
} p[LEN];

int N, L;
std::map<int, ll> U, D; // dp

int main() {
	std::cin >> N >> L;
	for (int i = 0; i < N; ++i) std::cin >> p[i].t >> p[i].d;

	std::sort(p, p + N);

	ll max = 0, u, d, l;
	for (int i = 0; i < N; ++i) {
		if (U.find(p[i].t) == U.end()) U[p[i].t] = 0;
		if (D.find(p[i].d) == D.end()) D[p[i].d] = 0;
		u = U[p[i].t];
		d = D[p[i].d];
		l = abs(p[i].t - p[i].d) + L;
		U[p[i].t] = std::max(u, d + l);
		D[p[i].d] = std::max(d, u + l);
		max = std::max({ max, U[p[i].t], D[p[i].d] });
	}
	std::cout << max;
}