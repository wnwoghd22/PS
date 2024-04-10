#include <iostream>

typedef long long ll;
ll gcd_count(ll a, ll b) {
	if (!b) return 0;
	ll result = a / b;
	return result + gcd_count(b, a % b);
}

int main() {
	ll A, B;
	std::cin >> A >> B;
	std::cout << gcd_count(A, B) - 1;
}