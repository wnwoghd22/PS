#include <iostream>
#include <cstring>

int table[6][6] = {
//  A  B  C  D     F
   10, 8, 7, 5, 0, 1, // A
	8, 6, 4, 3, 0, 1, // B
	7, 4, 3, 2, 0, 1, // C
	5, 3, 2, 2, 0, 1, // D
	0, 0, 0, 0, 0, 0, 
	1, 1, 1, 1, 0, 1  // F
};
int dp[14 * 14 + 1][1 << 14];
int N, M;
std::string val;

int F(int x, int bit) {
	if (x >= N * M) return 0;
	int& ref = dp[x][bit];
	if (~ref) return ref;

	if (bit & 1) ref = table[val[x] - 'A'][val[x - M] - 'A'] + F(x + 1, bit >> 1); // 1 * 2
	else {
		ref = F(x + 1, bit >> 1 | 1 << M - 1); // 1 * 2
		ref = std::max(ref, F(x + 1, bit >> 1)); // 1 * 1
		if (~(x % M - M) && ~bit & 2)
			ref = std::max(ref, table[val[x] - 'A'][val[x + 1] - 'A'] + F(x + 2, bit >> 2)); // 2 * 1
	}
	return ref;
}

int main() {
	std::cin >> N >> M;
	memset(dp, -1, sizeof dp);
	val = "";
	for (int i = 0; i < N; ++i) {
		std::string s; std::cin >> s;
		val += s;
	}
	std::cout << F(0, 0);
}