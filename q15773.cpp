#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
const int LEN = 250'000;

struct Balloon {
	ll l, d;
	bool operator<(const Balloon& r) const {
		return l + d < r.l + r.d;
	}
} b[LEN];

int N;

std::priority_queue<ll> pq;
ll h, k;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> b[i].l >> b[i].d;
	std::sort(b, b + N);

	h = b[0].d;
	pq.push(b[0].d);
	for (int i = 1; i < N; ++i) {
		if (h <= b[i].l) {
			h += b[i].d;
			pq.push(b[i].d);
		}
		else if (h - pq.top() <= b[i].l && b[i].d <= pq.top()) {
			h -= pq.top(); pq.pop();
			h += b[i].d; pq.push(b[i].d);
		}
	}
	std::cout << pq.size();
}