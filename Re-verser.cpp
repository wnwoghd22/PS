#include <iostream>
#include <algorithm>

const int LEN = 101;

char S[LEN];
int N, fail[LEN];
void kmp() {

}

int main() {
	int ans = 1;
	std::cin >> N >> S;
	for (int i = 1; i < N; ++i) {
		bool flag = 1;
		for (int j = i, k = 0; j < N; ++j, ++k) {
			if (S[j] ^ S[k]) {
				flag = 0;
				break;
			}
		}
		if (flag) ans = std::max(ans, N / i + !!(N % i));
	}
	std::cout << ans;
}