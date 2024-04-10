#include <iostream>

const int MOD = 1e9 + 7;
const int LEN = 1e5 + 1;

int N, A;

struct Fenwick {
	int t[LEN];
	int get(int i) {
		int result = 0;
		while (i > 0) {
			result += t[i];
			if (result >= MOD)
				result -= MOD;
			i -= i & -i;
		}
		return result;
	}
	void add(int i, int d) {
		while (i <= N) {
			t[i] += d;
			if (t[i] >= MOD)
				t[i] -= MOD;
			i += i & -i;
		}
	}
} dp[11];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		dp[0].add(A, 1);
		for (int j = 1; j < 11; ++j)
			dp[j].add(A, dp[j - 1].get(A - 1));
	}
	std::cout << dp[10].get(N);
}