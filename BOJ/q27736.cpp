#include <iostream>

int N, a, pro, con, non;
int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> a;
		(a == 1 ? pro : a ? con : non)++;
	}
	std::cout << (non * 2 >= N ? "INVALID" : pro > con ? "APPROVED" : "REJECTED");
}