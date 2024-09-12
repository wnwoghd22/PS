#include <iostream>

const int LEN = 1001;
const int CX[] = { 1, 1, 0, -1, -1 };
const int CY[] = { 1, -1, 0, 1, -1 };

const int DX[] = { 1, 0, -1, 0 };
const int DY[] = { 0, 1, 0, -1 };

int N, M, cnt;
char S[LEN][LEN];
bool v[LEN][LEN];

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		for (int j = 0; j < M; ++j) {
			if (S[i][j] == '*') cnt++;
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			bool cross = 1;
			for (int k = 0, nx, ny; k < 5; ++k) {
				nx = i + CX[k];
				ny = j + CY[k];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (S[nx][ny] == '.') cross = 0;
			}
			if (cross) {
				for (int k = 0, nx, ny; k < 5; ++k) {
					nx = i + CX[k];
					ny = j + CY[k];
					if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
					if (!v[nx][ny]) {
						v[nx][ny] = 1;
						cnt--;
					}
				}
			}
			bool donut = 1;
			for (int k = 0, nx, ny; k < 4; ++k) {
				nx = i + DX[k];
				ny = j + DY[k];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (S[nx][ny] == '.') donut = 0;
			}
			if (donut) {
				for (int k = 0, nx, ny; k < 4; ++k) {
					nx = i + DX[k];
					ny = j + DY[k];
					if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
					if (!v[nx][ny]) {
						v[nx][ny] = 1;
						cnt--;
					}
				}
			}
		}
	}
	std::cout << (cnt ? "NO" : "YES");
}