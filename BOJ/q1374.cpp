#include <iostream>
#include <algorithm>
#include <queue>

const int LEN = 1e5;

struct Lecture {
	int i, s, e;
	bool operator<(const Lecture& r) const { return s == r.s ? e < r.e : s < r.s; }
} L[LEN];

int N;
size_t cnt;
std::priority_queue<int> pq;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> L[i].i >> L[i].s >> L[i].e;
	std::sort(L, L + N);
	for (int i = 0; i < N; ++i) {
		while (pq.size() && -pq.top() <= L[i].s) pq.pop();
		pq.push(-L[i].e);
		cnt = std::max(cnt, pq.size());
	}
	std::cout << cnt;
}