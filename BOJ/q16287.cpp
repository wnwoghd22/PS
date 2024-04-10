#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef std::pair<int, int> pii;
const int W_MAX = 800'001;
const int LEN = 5001;
pii W[W_MAX];
int w, N, A[LEN];

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> w >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			int b = A[i] + A[j];
			W[b] = { i, j };
		}
	}
	bool flag = false;
	for (int i = 1; i < N && !flag; ++i) {
		for (int j = i + 1; j <= N && !flag; ++j) {
			int b = A[i] + A[j];
			const pii& c = W[w - b];
			if (!c.first) continue;
			if (i != c.first && i != c.second && j != c.first && j != c.second)
				flag = true;
		}
	}
	std::cout << (flag ? "YES" : "NO");
}