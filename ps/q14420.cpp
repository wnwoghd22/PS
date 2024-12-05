#include <iostream>
#include <queue>

typedef long long ll;
ll N, M, K, S0, S1;
ll A, B, C, T;

struct Cell {
	ll base, remains, s, e;
	int aug() const { return std::min(remains, (T - base) / A); }
	bool operator<(const Cell& o) const { return aug() < o.aug(); }
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	std::cin >> A >> B >> C >> T >> S0;
	ll ret = 0;
	std::priority_queue<Cell> pq;
	for (ll i = 1, cur, base, aug; i < M; ++i) {
		std::cin >> S1;
		cur = std::min((T - (S0 - 1) * B) / A, S1 - S0 - 1);
		std::cout << "express: " << S0 << " -> " << S1 << '\n';
		std::cout << "bound: " << cur << '\n';
		std::cout << T << '-' << S0 - 1 << '*' << B << '/' << A << '\n';
		ret += cur;
		base = (S0 - 1) * B + (cur + 1) * C;
		if (base <= T) {
			Cell nxt = { base, S1 - S0 - cur - 1, S0 + cur + 1, S1 - 1 };
			if (nxt.remains > 0) pq.push(nxt);
		}
		S0 = S1;
		if ((S0 - 1) * B > T) break;
		ret++;
	}
	K -= M;
	while (K-- && pq.size()) {
		Cell top = pq.top(); pq.pop();
		std::cout << "Cell: " << top.base << ' ' << top.remains << ' ' << top.s << ' ' << top.e << ' ' << top.aug() << '\n';
		ret += top.aug();
		if (top.base + (top.aug() + 1) * C <= T) {
			ret++;
			Cell nxt = { top.base + (top.aug() + 1) * C, top.remains - top.aug() - 1, top.s + top.aug() + 1, top.e };
			if (nxt.remains > 0) pq.push(nxt);
		}
	}
	std::cout << ret;
}
