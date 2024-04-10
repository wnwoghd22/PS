#include <iostream>

typedef long long ll;

int main() {
	ll N;
	std::cin >> N;
	while (~N & 1) N >>= 1;
	while (N % 3 == 0) N /= 3;
	std::cout << (N != 1 ? "No" : "Yes");
}