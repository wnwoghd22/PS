#include <iostream>

int main() {
	int N, A, ret = 0;
	std::cin >> N;
	while (--N) {
		std::cin >> A;
		ret -= A;
	}
	std::cout << ret;
}