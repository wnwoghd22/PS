#include <iostream>

const int LEN = 1e5 + 1;

int A, B, C, s[LEN];

int main() {
	for (int i = 2; i < LEN; ++i) {
		if (s[i]) continue;
		for (int j = i; j < LEN; j += i) s[j] = i;
	}
	std::cin >> A >> B;
	for (int i = A, j, k; i <= B; ++i) {
		j = i;
		k = 0;
		while (j > 1) {
			j /= s[j];
			++k;
		}
		if (s[k] == k) ++C;
	}
	std::cout << C;
}