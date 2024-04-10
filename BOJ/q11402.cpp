#include <iostream>

typedef long long int ll;
const int LEN = 2001;
int M, C[LEN][LEN];
ll N, K;

// Lucas
int main() {
	std::cin >> N >> K >> M;
	for (int i = 0; i < M; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;
	}

	int result = 1;
	while (N || K) {
		result = result * C[N % M][K % M] % M;
		N /= M, K /= M;
	}
	std::cout << result;
}