#include <iostream>
#include <cstring>

const int LEN = 1e5 + 1;

char S[LEN], T[4];

int main() {
	std::cin >> S >> T;
	int cnt = 0;
	for (int i = 0; S[i]; ++i) {
		if (S[i] - 'a' == T[cnt] - 'A')
			++cnt;
		if (cnt == 3) {
			std::cout << "Yes";
			return 0;
		}
	}
	std::cout << (cnt >= 2 && T[2] == 'X' ? "Yes" : "No");
}