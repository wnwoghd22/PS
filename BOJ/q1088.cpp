#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
typedef long double ld;
struct E {
	int w, c;
	ld f() const { return (ld)w / c; }
	bool operator<(const E& r) const { return (ll)w * r.c < (ll)r.w * c; }
};
std::priority_queue<E> pq;

int N, M, W;
ld min = 1e9, ret = 1e9;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> W;
		min = std::min(min, (ld)W);
		pq.push({ W, 1 });
	}
	std::cin >> M;
	ret = pq.top().w - min;
	while (M--) {
		E e = pq.top(); pq.pop();
		e.c++; min = std::min(min, e.f());
		pq.push(e); ret = std::min(ret, pq.top().f() - min);
	}
	(std::cout << std::fixed).precision(12);
	std::cout << ret;
}
