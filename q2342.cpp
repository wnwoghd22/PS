#include <iostream>
#include <cstring>

const int LEN = 100'001;
const int INF = 1e9;
int dp[LEN][11];
int N, dir[LEN + 1];
bool step[11][4] = {
	{ 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 },
	{ 1, 1, 0, 0 }, { 1, 0, 1, 0 }, { 1, 0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 }
};
int cost[11][11] = {
//	  0    1    2    3    4    5    6    7    8    9   10
	INF,   2,   2,   2,   2, INF, INF, INF, INF, INF, INF, // 0
	INF,   1,   3,   4,   3,   2,   2,   2, INF, INF, INF, // 1
	INF,   3,   1,   3,   4,   2, INF, INF,   2,   2, INF, // 2
	INF,   4,   3,   1,   3, INF,   2, INF,   2, INF,   2, // 3
	INF,   3,   4,   3,   1, INF, INF,   2, INF,   2,   2, // 4
	INF, INF, INF, INF, INF,   1,   3,   4,   4,   3, INF, // 5
	INF, INF, INF, INF, INF,   3,   1,   3,   3, INF,   3, // 6
	INF, INF, INF, INF, INF,   4,   3,   1, INF,   3,   4, // 7
	INF, INF, INF, INF, INF,   4,   3, INF,   1,   3,   4, // 8
	INF, INF, INF, INF, INF,   3, INF,   3,   3,   1,   3, // 9
	INF, INF, INF, INF, INF, INF,   3,   4,   4,   3,   1  // 10
};
int F(int n, int s) {
	if (!n) return !!s * INF;
	int d = dir[n] - 1;
	if (!step[s][d]) return INF;
	int& ref = dp[n][s];
	if (~ref) return ref;
	ref = INF;
	for (int i = 0; i < 11; ++i) {
		int f = F(n - 1, i) + cost[i][s];
		ref = std::min(ref, f);
	}
	return ref;
}
int main() {
	memset(dp, -1, sizeof dp);
	int a, result = INF;
	do {
		std::cin >> a;
		dir[++N] = a;
	} while (a);
	--N;
	for (int i = 0; i < 11; ++i) result = std::min(result, F(N, i));
	std::cout << result;
}