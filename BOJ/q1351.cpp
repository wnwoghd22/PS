#include <iostream>
#include <map>

typedef long long ll;
std::map<ll, ll> f;
ll N, P, Q;

ll A(ll n) {
	if (f.find(n) != f.end()) return f[n];
	return f[n] = A(n / P) + A(n / Q);
}
int main() {
	f[0] = 1;
	std::cin >> N >> P >> Q;
	std::cout << A(N);
}