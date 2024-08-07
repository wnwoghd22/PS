#include <iostream>
#include <cstring>

const int LEN = 1e6 + 1;

char S[LEN], T[LEN], st[LEN];
int ls, lt, sp, fail[101], s[LEN];

int main() {
	std::cin >> S >> T;
	ls = strlen(S);
	lt = strlen(T);
	for (int i = 1, j = 0; i < lt; ++i) {
		while (j > 0 && T[j] != T[i]) j = fail[j - 1];
		if (T[j] == T[i]) fail[i] = ++j;
	}
	for (int i = 0; i < ls; ++i) {
		int j = sp ? s[sp - 1] : 0;
		st[sp++] = S[i];
		while (j > 0 && S[i] != T[j]) j = fail[j - 1];
		if (S[i] == T[j]) ++j;
		if (j == lt) sp -= lt;
		else s[sp - 1] = j;
	}
	for (int i = 0; i < sp; ++i) std::cout << st[i];
}