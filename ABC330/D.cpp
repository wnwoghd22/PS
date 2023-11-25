#include <iostream>

typedef long long ll;
const int LEN = 2001;

char S[LEN][LEN];

int N;
ll row[LEN], col[LEN];
ll answer;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		for (int j = 0; j < N; ++j) {
			if (S[i][j] == 'o') {
				row[i + 1]++;
				col[j + 1]++;
			}
		}
	}
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (S[i - 1][j - 1] == 'o')
				answer += (row[i] - 1) * (col[j] - 1);
	std::cout << answer;
}