#include <iostream>
#include <map>

typedef long long ll;
const int LEN = 1e5;
const int INF = 1e9;

int N, X[LEN];

ll f(ll d) {
	static std::map<ll, ll> map;
	if (map.find(d) != map.end()) return map[d];
	ll cost = 0;
	for (int i = 0; i < N; ++i)
		cost += std::abs(X[i] - d * i);
	return map[d] = cost;
}

ll ternary_search() {
	ll s = 0, e = INF, l, r;
	ll ret = INF * INF;
	while (e - s > 2) {
		l = (s + s + e) / 3;
		r = (s + e + e) / 3;
		ll cl = f(l), cr = f(r);
		if (cl > cr) s = l;
		else e = r;
	}
	for (int i = s; i <= e; ++i) ret = std::min(ret, f(i));
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> X[i];
	std::cout << ternary_search();
}