#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

typedef long long int ll;
typedef std::pair<ll, ll> pii;
const ll INF = 1e17;
const int MAX = 100'001;
std::vector<pii> pos;
std::vector<std::vector<pii>> a;
ll dp[MAX][2][2][2];
ll N, Plr, Pj;

ll cost(int i1, int j1, bool jumped, int i2, int j2, bool jump) {
	auto [x1, y1] = a[i1][j1]; y1 -= jumped;
	auto [x2, y2] = a[i2][j2]; y2 -= jump;

	if (y2 <= 0 || abs(x1 - x2) > y2 - y1) return INF;
	return abs(x1 - x2) * Plr + jump * Pj;
}

ll f(int i, int j, bool jumped, bool visited) {
	ll& ref = dp[i][j][jumped][visited];
	if (~ref) return ref;

	ref = INF;
	if (a[i].size() == 2 && !visited) {
		ll c1 = cost(i, j, jumped, i, !j, 0) + f(i, !j, 0, true);
		ll c2 = cost(i, j, jumped, i, !j, 1) + f(i, !j, 1, true);
		ref = std::min({ ref, c1, c2 });
	}
	else {
		if (i == a.size() - 1) return ref = 0;
		for (int e = 0; e < a[i + 1].size(); ++e) {
			ll c1 = cost(i, j, jumped, i + 1, e, 0) + f(i + 1, e, 0, false);
			ll c2 = cost(i, j, jumped, i + 1, e, 1) + f(i + 1, e, 1, false);
			ref = std::min({ ref, c1, c2 });
		}
	}
	return ref;
}

int main() {
	std::cin >> N >> Plr >> Pj;
	pos.resize(N);
	for (int i = 0; i < N; ++i) std::cin >> pos[i].first >> pos[i].second;
	std::sort(pos.begin(), pos.end(), [&](const pii& l, const pii& r) { return l.second < r.second; });
	int cy = 0;
	a.push_back({ {0, 0} });
	for (const auto& [x, y] : pos) {
		if (cy ^ y) cy = y, a.push_back({});
		a.back().push_back({x, y});
		if (a.back().size() >= 3) {
			std::cout << -1;
			return 0;
		}
	}
	memset(dp, -1, sizeof dp);

	ll result = f(0, 0, 0, 0);
	if (result >= INF) std::cout << -1;
	else std::cout << result;
}