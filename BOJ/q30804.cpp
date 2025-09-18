#include <iostream>

const int LEN = 200'001;
int N, S[LEN], C[10];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	int ret = 0;
	for (int i = 0, j = 0, c = 0; i < N; ++i) {
		std::cin >> S[i];
		if (!C[S[i]]++) c++;
		while (c > 2) if (!--C[S[j++]]) c--;
		ret = std::max(ret, i - j + 1);
	}
	std::cout << ret;
}