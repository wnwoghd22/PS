#include <iostream>

int main() {
	int N, A1, A;
	std::cin >> N >> A1;
	int result = -1;
	for (int i = 2; i <= N; ++i) {
		std::cin >> A;
		if (A > A1) {
			result = i;
			break;
		}
	}
	std::cout << result;
}