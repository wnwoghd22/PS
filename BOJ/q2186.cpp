#include <iostream>
#include <cstring>

const int LEN = 101;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int N, M, K, L;
char map[LEN][LEN], S[LEN];
int dp[2][LEN][LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	for (int i = 0; i < N; ++i)
		std::cin >> map[i];
	std::cin >> S;
	L = strlen(S);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			if (map[i][j] == S[0])
				dp[0][i][j] = 1;
	}
	for (int l = 1; S[l]; ++l) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				dp[l & 1][i][j] = 0;
				if (map[i][j] != S[l]) continue;
				for (int d = 0; d < 4; ++d) {
					for (int k = 1; k <= K; ++k) {
						int nx = i + dx[d] * k;
						int ny = j + dy[d] * k;
						if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
						if (map[nx][ny] == S[l - 1]) dp[l & 1][i][j] += dp[~l & 1][nx][ny];
					}
				}
			}
		}
	}
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			ret += dp[~L & 1][i][j];
	}
	std::cout << ret;
}
