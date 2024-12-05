#include <iostream>
#include <queue>

typedef long long ll;
ll N, M, K, S0, S1;
ll A, B, C, T;

struct Cell {
	ll base, remains;
	int aug() const { return std::min(remains, (T - base) / A); }
	bool operator<(const Cell& o) const { return aug() < o.aug(); }
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	std::cin >> A >> B >> C >> T >> S0;
	ll ret = -1;
	std::priority_queue<Cell> pq;
	for (ll i = 1, cur, base, aug; i < M; ++i) {
		std::cin >> S1;
		cur = (T - (S0 - 1) * B) / A;
		ret += std::min(cur, S1 - S0 - 1);
		base = (S0 - 1) * B + (cur + 1) * C;
		if (base <= T) {
			ret++;
			Cell nxt = { base, S1 - S0 - cur - 1 };
			if (nxt.remains > 0) pq.push(nxt);
		}
		S0 = S1;
		if ((S0 - 1) * B > T) break;
		ret++;
	}
	K -= M;
	while (K-- && pq.size()) {
		Cell top = pq.top(); pq.pop();
		std::cout << top.aug() << ' ';
		ret += top.aug();
		if (top.base + (top.aug() + 1) * C <= T) {
			ret++;
			Cell nxt = { top.base + (top.aug() + 1) * C, top.remains - top.aug() - 1 };
			if (nxt.remains > 0) pq.push(nxt);
		}
	}
	std::cout << ret;
}
