#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e7 + 1;

ll A, B, s[LEN];

int main() {
	std::cin >> A >> B;
	for (int i = 1; i < B; ++i) {
		for (int j = i * 2; j <= B; j += i)
			s[j] += i;
	}
	ll ret = 0;
	for (ll i = A; i <= B; ++i) ret += std::abs(i - s[i]);
	std::cout << ret;
}