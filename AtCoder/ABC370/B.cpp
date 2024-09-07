#include <iostream>

const int LEN = 101;

int N, A[LEN][LEN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= i; ++j) {
			std::cin >> A[i][j];
			A[j][i] = A[i][j];
		}
	}
	int ret = 1;
	for (int i = 1; i <= N; ++i) ret = A[ret][i];
	std::cout << ret;
}