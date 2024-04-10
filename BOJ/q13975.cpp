#include <iostream>
#include <queue>

typedef long long int ll;

int main() {
	ll T, N, A;
	std::cin >> T;
	while (T--) {
		std::priority_queue<ll> pq;
		std::cin >> N;
		while (N--) {
			std::cin >> A;
			pq.push(-A);
		}
		ll result = 0;
		while (pq.size() > 1) {
			ll a1 = pq.top(); pq.pop();
			ll a2 = pq.top(); pq.pop();
			ll cost = a1 + a2;
			result -= cost;
			pq.push(cost);
		}
		std::cout << result << '\n';
	}
	
}