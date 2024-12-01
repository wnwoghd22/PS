#include <iostream>

typedef long long ll;
ll N, len, d[10], l[10], r[10];

int main() {
	std::cin >> N;
	while (N) d[len++] = N % 10, N /= 10;
	l[0] = d[0];
	for (int i = 1; i < len; ++i) l[i] = l[i - 1] * d[i];
	r[len - 1] = d[len - 1];
	for (int i = len - 1; i > 0; --i) r[i - 1] = r[i] * d[i - 1];

	for (int i = 0; i < len - 1; ++i) {
		if (l[i] == r[i + 1]) {
			std::cout << "YES";
			return 0;
		}
	}
	std::cout << "NO";
}