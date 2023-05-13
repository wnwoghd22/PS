#include <iostream>

const int ATCODER = 671773;
int cs, s[26], req_s;
int ct, t[26], req_t;

int main() {
	bool result = true;
	std::string S, T;
	std::cin >> S >> T;
	for (const char& c : S) (c == '@' ? cs : s[c - 'a'])++;
	for (const char& c : T) (c == '@' ? ct : t[c - 'a'])++;
	for (int i = 0; i < 26; ++i) {
		if ((1 << i) & ATCODER) {
			if (s[i] > t[i]) {
				req_t += s[i] - t[i];
			}
			else req_s += t[i] - s[i];
		}
		else {
			if (s[i] ^ t[i]) {
				result = false;
				break;
			}
		}
	}
	if (result) {
		if (cs < req_s || ct < req_t)
			result = false;
	}
	std::cout << (result ? "Yes" : "No");
}