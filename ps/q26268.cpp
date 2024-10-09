#include <iostream>
#include <algorithm>

typedef long long int ll;
struct Bank { ll X, T, C; };
const int LEN = 300'001;
Bank b[LEN];
ll dp[LEN][2][2];
int N;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> b[i].X >> b[i].T >> b[i].C;
	}

	for (int i = 0; i < N; ++i) {
		// dp[i + 1][0][0] = 
	}
}