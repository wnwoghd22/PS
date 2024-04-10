#include <iostream>

typedef long long int ll;
ll N, S_1 = 0, S;

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> S;
		std::cout << S - S_1 << ' ';
		S_1 = S;
	}
}