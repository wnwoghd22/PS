#include <iostream>
#include <cstring>

int main() {
	char S[10];
	std::cin >> S;
	int len = strlen(S);
	int idx = -1;
	for (int i = 0; i < 10; ++i) {
		if (S[i] == '.') idx = i;
	}
	if (~idx) {
		for (int i = len - 1; i > idx; --i) {
			if (S[i] == '0') S[i] = 0;
			else break;
		}
		if (S[idx + 1] == 0) S[idx] = 0;
	}
	std::cout << S;
}