#include <iostream>
#include <algorithm>

const int LEN = 2001;

int N, M, K;
std::string board[LEN];
int bwB[LEN][LEN];
int bwW[LEN][LEN];
int wbB[LEN][LEN];
int wbW[LEN][LEN];

int main() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) std::cin >> board[i];
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if ((i ^ j) & 1) {
				if (board[i - 1][j - 1] == 'B') bwW[i][j] = 1;
				if (board[i - 1][j - 1] == 'W') wbB[i][j] = 1;
			}
			else {
				if (board[i - 1][j - 1] == 'B') wbW[i][j] = 1;
				if (board[i - 1][j - 1] == 'W') bwB[i][j] = 1; 
			}
			bwB[i][j] += bwB[i - 1][j] + bwB[i][j - 1] - bwB[i - 1][j - 1];
			bwW[i][j] += bwW[i - 1][j] + bwW[i][j - 1] - bwW[i - 1][j - 1];
			wbB[i][j] += wbB[i - 1][j] + wbB[i][j - 1] - wbB[i - 1][j - 1];
			wbW[i][j] += wbW[i - 1][j] + wbW[i][j - 1] - wbW[i - 1][j - 1];
		}
	}
	int result = K * K;

	for (int i = K; i <= N; ++i) {
		for (int j = K; j <= M; ++j) {
			int bw = bwB[i][j] - bwB[i - K][j] - bwB[i][j - K] + bwB[i - K][j - K]
				+ bwW[i][j] - bwW[i - K][j] - bwW[i][j - K] + bwW[i - K][j - K];
			int wb = wbB[i][j] - wbB[i - K][j] - wbB[i][j - K] + wbB[i - K][j - K]
				+ wbW[i][j] - wbW[i - K][j] - wbW[i][j - K] + wbW[i - K][j - K];
			result = std::min({ bw, wb, result });
		}
	}
	std::cout << result;
}