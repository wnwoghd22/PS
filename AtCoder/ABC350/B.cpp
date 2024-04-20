#include <iostream>

bool a[1001];
int N, Q, T;

int main() {
	std::cin >> N >> Q;
	while (Q--) {
		std::cin >> T;
		if (a[T]) {
			a[T] = 0;
			N++;
		}
		else {
			a[T] = 1;
			N--;
		}
	}
	std::cout << N;
}