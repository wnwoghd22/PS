#include <iostream>
#include <queue>

typedef long long ll;
std::priority_queue<ll> pq;

ll N, M, A, S, x, y, z;
int main() {
	std::cin >> N >> M;
	while (N--) {
		std::cin >> A;
		pq.push(-A);
	}
	while (M--) {
		x = pq.top(); pq.pop();
		y = pq.top(); pq.pop();
		std::cout << x << ' ' << y << '\n';
		z = x + y;
		pq.push(z); pq.push(z);
	}
	while (pq.size()) std::cout << pq.top(), S -= pq.top(), pq.pop();
	std::cout << S;
}