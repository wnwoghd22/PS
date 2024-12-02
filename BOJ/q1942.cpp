#include <iostream>

std::string S;
int sh, sm, ss;
int eh, em, es;


int main() {
	while (std::cin >> S) {
		sh = (S[0] - '0') * 10 + S[1] - '0';
		sm = (S[3] - '0') * 10 + S[4] - '0';
		ss = (S[6] - '0') * 10 + S[7] - '0';

		std::cin >> S;
		eh = (S[0] - '0') * 10 + S[1] - '0';
		em = (S[3] - '0') * 10 + S[4] - '0';
		es = (S[6] - '0') * 10 + S[7] - '0';

		int ret = (eh + em + es) % 3 == 0;
		while (sh != eh || sm != em || ss != es) {
			ret += (sh + sm + ss) % 3 == 0;
			ss++;
			if (ss >= 60) sm++, ss = 0;
			if (sm >= 60) sh++, sm = 0;
			if (sh >= 24) sh = 0;
		}
		std::cout << ret << '\n';
	}
}