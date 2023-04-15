#include <iostream>

bool A[100][100], B[100][100], temp[100][100];
int N;

void rotate(int n) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			temp[j][n - i - 1] = A[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			A[i][j] = temp[i][j];
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> A[i][j];

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> B[i][j];

	for (int k = 0; k < 4; ++k) {
		bool flag = false;
		rotate(N);

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (A[i][j] && !B[i][j]) {
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag) {
			std::cout << "Yes";
			return 0;
		}
	}
	std::cout << "No";
	return 0;
}