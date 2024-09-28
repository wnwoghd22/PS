#include <iostream>

const int LEN = 2002;

int N, H[LEN], sp, S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	int ret = 0;
	for (int i = 0; i < N; ++i) {
        sp = 0;
        for (int j = 1, a; j <= N; ++j) {
            std::cin >> a;
            if (a) H[j] = 0;
            else ++H[j];
        }
        for (int j = 0, k; j <= N + 1; ++j) {
            while (sp && H[S[sp - 1]] > H[j]) {
                k = S[--sp];
                ret = std::max(ret, H[k] * (j - S[sp - 1] - 1));
            }
            S[sp++] = j;
        }
	}
    std::cout << ret;
}