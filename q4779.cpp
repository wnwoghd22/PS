#include <iostream>

void f(int k) {
	if (!k) { std::cout << '-'; return; }

	f(k - 1);

	int n = 1;
	for (int i = 1; i < k; ++i) n *= 3;
	for (int i = 0; i < n; ++i) std::cout << ' ';

	f(k - 1);
}

int main() {
	int N;
	while (std::cin >> N) {
		f(N);
		std::cout << '\n';
	}

}