#include <iostream>

int board[6][20][20];
bool merged[20][20];
int N;

void sweep_u(int t) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			board[t + 1][i][j] = merged[i][j] = 0;

	for (int i = 0; i < N; ++i) {
		int u = 0, d = -1;
		while (++d < N) {
			if (!board[t][d][i]) continue;
			if (!board[t + 1][u][i]) board[t + 1][u][i] = board[t][d][i];
			else {
				if (board[t + 1][u][i] == board[t][d][i] && !merged[u][i]) {
					merged[u][i] = true;
					board[t + 1][u][i] += board[t][d][i];
				}
				else board[t + 1][++u][i] = board[t][d][i];
			}
		}
	}
}
void sweep_d(int t) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			board[t + 1][i][j] = merged[i][j] = 0;

	for (int i = 0; i < N; ++i) {
		int u = N, d = N - 1;
		while (--u >= 0) {
			if (!board[t][u][i]) continue;
			if (!board[t + 1][d][i]) board[t + 1][d][i] = board[t][u][i];
			else {
				if (board[t + 1][d][i] == board[t][u][i] && !merged[d][i]) {
					merged[d][i] = true;
					board[t + 1][d][i] += board[t][u][i];
				}
				else board[t + 1][--d][i] = board[t][u][i];
			}
		}
	}
}
void sweep_l(int t) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			board[t + 1][i][j] = merged[i][j] = 0;

	for (int i = 0; i < N; ++i) {
		int l = 0, r = -1;
		while (++r < N) {
			if (!board[t][i][r]) continue;
			if (!board[t + 1][i][l]) board[t + 1][i][l] = board[t][i][r];
			else {
				if (board[t + 1][i][l] == board[t][i][r] && !merged[i][l]) {
					merged[i][l] = true;
					board[t + 1][i][l] += board[t][i][r];
				}
				else board[t + 1][i][++l] = board[t][i][r];
			}
		}
	}
}
void sweep_r(int t) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			board[t + 1][i][j] = merged[i][j] = 0;

	for (int i = 0; i < N; ++i) {
		int l = N, r = N - 1;
		while (--l >= 0) {
			if (!board[t][i][l]) continue;
			if (!board[t + 1][i][r]) board[t + 1][i][r] = board[t][i][l];
			else {
				if (board[t + 1][i][r] == board[t][i][l] && !merged[i][r]) {
					merged[i][r] = true;
					board[t + 1][i][r] += board[t][i][l];
				}
				else board[t + 1][i][--r] = board[t][i][l];
			}
		}
	}
}
void (*sweep[4])(int) = { sweep_u, sweep_d, sweep_l, sweep_r };

int get_max(int t) {
	int max = 0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (board[t][i][j] > max)
				max = board[t][i][j];
	return max;
}
int dfs(int t) {
	if (t == 5) return get_max(5);
	int result = 0;
	for (int i = 0; i < 4; ++i) {
		sweep[i](t);
		result = std::max(result, dfs(t + 1));
	}
	return result;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> board[0][i][j];
		}
	}
	/*sweep_l(0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << board[1][i][j] << ' ';
		}
		std::cout << '\n';
	}*/
	std::cout << dfs(0);
}