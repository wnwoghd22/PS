#include <iostream>

typedef long long ll;

ll N, n, ret;
int K, i, f, a[60];

int main() {
	std::cin >> N >> K;
	for (i = 0, n = N; n; ++i, n /= K) a[i] = n % K;
	for (int j = (i - (~i & 1)) - 1; j >= 0; j -= 2) {
		ret *= K;
		if (!f) {
			if (a[j + 1]) ret += K, f = 1;
			else ret += a[j];
		}
	}
	std::cout << ret + !f;
}