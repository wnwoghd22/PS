#include <iostream>
#include <queue>

typedef long long ll;
const int LEN = 1'000'001;

int N, A[LEN];
std::priority_queue<int> pq;

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	
	ll ret = 0;
	for (int i = 1; i <= N; ++i) {
		if (pq.size() && A[i] - i < pq.top()) {
			ret += pq.top() - A[i] + i;
			pq.pop(); pq.push(A[i] - i);
		}
		pq.push(A[i] - i);
	}
	std::cout << ret;
}