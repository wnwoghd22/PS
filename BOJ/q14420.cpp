#include <iostream>
#include <queue>

typedef long long ll;
ll N, M, K, S0, S1;
ll A, B, C, T;

struct Cell {
	ll base, s, e;
	int aug() const { return std::min(e - s + 1, (T - base) / A + 1); }
	bool operator<(const Cell& o) const { return aug() < o.aug(); }
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	std::cin >> A >> B >> C >> T >> S0;
	ll ret = 0; S0--;
	std::priority_queue<Cell> pq;
	for (ll i = 1, cur, base; i < M; ++i) {
		std::cin >> S1; S1--;
		cur = std::min((T - S0 * B) / A, S1 - S0 - 1);
		ret += cur;
		base = S0 * B + (cur + 1) * C;
		if (base <= T) {
			Cell nxt = { base, S0 + cur + 1, S1 - 1 };
			if (nxt.aug() > 0) pq.push(nxt);
		}
		S0 = S1;
		if (S0 * B > T) break;
		ret++;
	}
	K -= M;
	while (K-- && pq.size()) {
		Cell top = pq.top(); pq.pop();
		ret += top.aug();
		if (top.base + top.aug() * C <= T) {
			Cell nxt = { top.base + top.aug() * C, top.s + top.aug(), top.e };
			if (nxt.aug() > 0) pq.push(nxt);
		}
	}
	std::cout << ret;
}
