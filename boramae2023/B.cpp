#include <iostream>
#include <queue>

typedef long long ll;

std::priority_queue<int> pq;

int N, M, A, I;
ll P;
int main() {
	std::cin >> N >> M >> P;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> A;
			if (A < 0) ++I;
			else pq.push(-A);
		}
		while (pq.size()) {
			while (P < -pq.top()) {
				if (!I) {
					std::cout << 0;
					return 0;
				}
				--I, P <<= 1;
			}
			P -= pq.top();
			pq.pop();
		}
		while (I) --I, P <<= 1;
	}
	std::cout << 1;
}