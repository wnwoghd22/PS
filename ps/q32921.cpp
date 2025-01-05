#include <iostream>

int N, t[20];
char S[5];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		t[i] = (S[0] - '7') * 60 + (S[2] - '0') * 10 + S[3] - '0';
	}
	// for (int i = 0; i < N; ++i) std::cout << t[i] << ' ';
	int ret = 2;
	for (int i = 0; i < N - 1; ++i) {
		if (t[i + 1] - t[i] <= 10) ret = 1;
	}
	for (int i = 0; i < N - 2; ++i) {
		if (t[i + 2] - t[i] <= 10) ret = 0;
	}
	std::cout << ret;
}