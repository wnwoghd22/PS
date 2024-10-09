#include <iostream>
#include <queue>

typedef long long int ll;
const ll MOD = 2'000'003;
bool P[MOD];
int N;

int main() {
	ll result = 1;
	std::priority_queue<ll> q;
	for (ll i = 2, j; i < MOD; ++i) {
		if (P[i]) continue;
		j = i;
		while (j <= MOD) q.push(-j), j *= j;
		for (j = i * 2; j < MOD; j += i) P[j] = true;
	}

	std::cin >> N;
	while (N--) result = result * -q.top() % MOD, q.pop();
	std::cout << result;
}