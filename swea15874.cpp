#include <iostream>
#include <cstring>

typedef long long int ll;
const int LEN = 4000;
ll N, K, M, dp1[LEN], dp2[LEN];
ll *p1, *p2, *temp;

ll factorial(ll k) {
	ll result = 1;
	for (ll i = 2; i <= k; ++i) result = result * i % M;
	return result;
}

ll modulo(ll a, ll n) {

}

int solve() {
	std::cin >> N >> K >> M;

}

int main() {
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {

	}
}