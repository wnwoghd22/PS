#include <iostream>

int main() {
	int N, D;
	int t1, t2;
	int result = -1;
	std::cin >> N >> D >> t1;
	while (--N) {
		std::cin >> t2;
		if (t2 - t1 <= D) {
			result = t2;
			break;
		}
		t1 = t2;
	}
	std::cout << result;
}