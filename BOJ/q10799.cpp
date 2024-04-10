#include <iostream>

const int LEN = 100'001;
int p, q, r;
char s[LEN];

int main() {
	std::cin >> s;
	for (p; s[p]; ++p) {
		if (s[p] == ')') {
			--q;
			if (s[p - 1] == '(') r += q;
			else ++r;
		}
		else ++q;
	}
	std::cout << r;
}