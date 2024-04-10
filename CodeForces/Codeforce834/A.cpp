#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::string s;
		std::cin >> s;
		int c;
		if (s[0] == 'Y') c = 0;
		else if (s[0] == 'e') c = 1;
		else if (s[0] == 's') c = 2;
		else c = -1;
		if (!~c) {
			std::cout << "NO\n";
		}
		else {
			for (int i = 0; i < s.length(); ++i) {
				if (s[i] == 'Y') {
					if (c != 0) c = -1;
				}
				else if (s[i] == 'e') {
					if (c != 1) c = -1;
				}
				else if (s[i] == 's') {
					if (c != 2) c = -1;
				}
				else c = -1;


				if (c == -1) break;
				c = (c + 1) % 3;
			}

			if (~c) std::cout << "YES\n";
			else std::cout << "NO\n";
		}
	}
}