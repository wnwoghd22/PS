#include <iostream>

typedef long long int ll;

int main() {
	ll N, A;
	std::cin >> N;
	ll a = 0, sum = 0;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		a += A;
		sum -= A * i;
	}

	if (!a) {
		if (sum) {
			std::cout << "No";
		}
		else {
			std::cout << "Yes\n";
			for (int i = 0; i < N; ++i) {
				std::cout << i << ' ';
			}
		}
	}
	else {
		if (!sum) {
			std::cout << "Yes\n";
			for (int i = 0; i < N; ++i) {
				std::cout << i << ' ';
			}
		}
		else {
			if (sum % a) std::cout << "No";
			else {
				ll a0 = sum / a;
				std::cout << "Yes\n";
				for (int i = 0; i < N; ++i) {
					std::cout << a0 + i << ' ';
				}
			}
		}
	}
}