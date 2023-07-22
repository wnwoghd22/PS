#include <iostream>
#include <algorithm>
#include <queue>

const int LEN = 10000;

struct Lecture {
	int d, p;
	bool operator<(const Lecture& r) const {
		return d < r.d;
	}
} a[LEN];

int N, S;

std::priority_queue<int> pq;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> a[i].p >> a[i].d;
	std::sort(a, a + N);

	for (int i = 0; i < N; ++i) {
		if (pq.size() < a[i].d) {
			S += a[i].p;
			pq.push(-a[i].p);
		}
		else if (pq.top() > -a[i].p) {
			S += pq.top(); pq.pop();
			S += a[i].p;
			pq.push(-a[i].p);
		}
	}
	std::cout << S;
}