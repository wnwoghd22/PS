#include <iostream>
#include <algorithm>

const int LEN = 100;
std::string S[LEN];

int main() {
	int N, rate = 0;
	std::cin >> N;
	for (int i = 0, r; i < N; ++i) {
		std::cin >> S[i] >> r;
		rate += r;
	}
	std::sort(S, S + N);
	std::cout << S[rate % N];
}