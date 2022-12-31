#include <iostream>
#include <cmath>

typedef long long int ll;

ll sum(ll x) {
	ll result = 0;
	for (int i = 1; i <= sqrt(x); ++i) {
		if (x % i == 0) {
			result += i;
			if (i != 1 && i != sqrt(x)) result += x / i;
		}
	}
	return result;
}

ll check(ll x) {
	ll s = sum(x);
	if (s > x) {
		for (int i = 1; i <= sqrt(x); ++i) {
			if (x % i == 0) {
				if (sum(i) > i) return false;
				if (i != 1 && i != sqrt(x)) {
					int p = x / i;
					if (sum(p) > p) return false;
				}
			}
		}
		return true;
	}
	return false;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll N;
		std::cin >> N;
		if (check(N)) {
			std::cout << "Good Bye\n";
		}
		else {
			std::cout << "BOJ 2022\n";
		}
	}
}