#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 1001;
int N, mex[LEN] = { 0, 0, 1, };
bool visited[10];

int main() {
	freopen("input.txt", "r", stdin);
	for (int i = 3; i < LEN; ++i) {
		memset(visited, 0, sizeof visited);
		for (int j = 0; j <= (i - 1 >> 1); ++j) {
			visited[mex[j] ^ mex[i - j - 2]] = 1;
		}
		for (int j = 0; j < 10; ++j) {
			if (!visited[j]) {
				mex[i] = j;
				break;
			}
		}
	}
	// for (int i = 0; i < LEN; ++i) std::cout << "mex[" << i << "] = " << mex[i] << '\n';
	while (std::cin >> N) std::cout << (1 + !mex[N]) << '\n';
}