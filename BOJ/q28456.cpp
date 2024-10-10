#include <iostream>

int N, Q, r, arr[100][100];

void rotate(int i) {
	int temp;
	int x = N - i - 1;
	if (r == 0) {
		temp = arr[i][N - 1];
		for (int j = N - 1; j > 0; --j) arr[i][j] = arr[i][j - 1];
		arr[i][0] = temp;
	}
	if (r == 1) {
		temp = arr[0][i];
		for (int j = 0; j < N - 1; ++j) arr[j][i] = arr[j + 1][i];
		arr[N - 1][i] = temp;
	}
	if (r == 2) {
		temp = arr[x][0];
		for (int j = 0; j < N - 1; ++j) arr[x][j] = arr[x][j + 1];
		arr[x][N - 1] = temp;
	}
	if (r == 3) {
		temp = arr[N - 1][x];
		for (int j = N - 1; j > 0; --j) arr[j][x] = arr[j - 1][x];
		arr[0][x] = temp;
	}
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> arr[i][j];

	std::cin >> Q;
	for (int k = 0, q, i; k < Q; ++k) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i;
			rotate(i - 1);
		}
		if (q == 2) r = (r + 1) % 4;
	}

	if (r == 0) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j)
				std::cout << arr[i][j] << ' ';
			std::cout << '\n';
		}
	}
	if (r == 1) {
		for (int j = 0; j < N; ++j) {
			for (int i = N - 1; i >= 0; --i)
				std::cout << arr[i][j] << ' ';
			std::cout << '\n';
		}
	}
	if (r == 2) {
		for (int i = N - 1; i >= 0; --i) {
			for (int j = N - 1; j >= 0; --j)
				std::cout << arr[i][j] << ' ';
			std::cout << '\n';
		}
	}
	if (r == 3) {
		for (int j = N - 1; j >= 0; --j) {
			for (int i = 0; i < N; ++i)
				std::cout << arr[i][j] << ' ';
			std::cout << '\n';
		}
	}
}