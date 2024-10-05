#include <iostream>

char s[500'001];

const char* K = "KOREA";
const char* Y = "YONSEI";

int main() {
	std::cin >> s;
	int sk = 0, sy = 0;
	for (int i = 0; s[i]; ++i) {
		if (s[i] == Y[sy]) ++sy;
		if (s[i] == K[sk]) ++sk;
		if (sy == 6 || sk == 5) break;
	}
	if (sk == 5) std::cout << K;
	if (sy == 6) std::cout << Y;
}