#include <iostream>

const int LEN = 101;
char S[LEN];
int C[LEN];
int cnt[LEN];

int main() {
	std::cin >> S;
	for (int i = 0; S[i]; ++i) C[S[i] - 'a']++;
	for (int i = 0; i < LEN; ++i) cnt[C[i]]++;
	for (int i = 1; i < LEN; ++i) {
		// std::cout << cnt[i] << '\n';
		if (cnt[i] == 0 || cnt[i] == 2) continue;
		else {
			std::cout << "No";
			return 0;
		}
	}
	std::cout << "Yes";
}