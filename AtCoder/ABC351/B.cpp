#include <iostream>

const int LEN = 101;

char A[LEN][LEN];
char B[LEN][LEN];
int N, r, c;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; ++i) std::cin >> B[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (A[i][j] != B[i][j]) {
				r = i + 1;
				c = j + 1;
			}
		}
	}
	std::cout << r << ' ' << c;
}
