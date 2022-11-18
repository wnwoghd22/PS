#include <iostream>

typedef long long int ll;

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll n, m;
		std::cin >> n >> m;
		ll n2 = 0, n5 = 0, temp;
		temp = n;
		while (!(temp % 2)) temp /= 2, n2++;
		temp = n;
		while (!(temp % 5)) temp /= 5, n5++;

		temp = 1;
		for (int i = 0; i < n2 - n5 && temp * 5 <= m; ++i) temp *= 5;
		for (int i = 0; i < n5 - n2 && temp * 2 <= m; ++i) temp *= 2;

		while (temp * 10 <= m) temp *= 10;

		ll result = temp;

		while (result + temp <= m) result += temp;

		std::cout << n * result << '\n';
	}
}