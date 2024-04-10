#include <iostream>

const int LEN = 31;
char S[LEN];
int sp, s[LEN];

int main() {
	std::cin >> S;
	for (int i = 0; S[i]; ++i) {
		if (S[i] == '(') s[sp++] = -2;
		if (S[i] == '[') s[sp++] = -3;
		if (S[i] == ')' || S[i] == ']') {
			if (!sp) {
				std::cout << 0;
				return 0;
			}
			int x = S[i] == ')' ? 2 : 3;
			int cur = s[sp - 1] < 0;
			while (sp && s[sp - 1] > 0) cur += s[--sp];
			if (!sp || s[sp - 1] + x) {
				std::cout << 0;
				return 0;
			}
			s[sp - 1] = cur * x;
		}
	}
	int ret = 0;
	while (sp) {
		if (s[sp - 1] < 0) {
			ret = 0;
			break;
		}
		ret += s[--sp];
	}
	std::cout << ret;
}