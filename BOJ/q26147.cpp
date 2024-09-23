#include <iostream>

std::string S[100'000];
char s[6];

int main() {
	std::string answer = "ABCDE";
	int N, flag = 1;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		if (S[i] == "GGGGY" ||
			S[i] == "GGGYG" ||
			S[i] == "GGYGG" ||
			S[i] == "GYGGG" ||
			S[i] == "YGGGG"
			) flag = 0;
	}
	if (flag) {
		std::cout << answer << '\n';
		for (int i = 0; i < N; ++i) {
			for (int k = 0, j = 0; j < 5; ++j) {
				switch (S[i][j]) {
				case 'G':
					s[j] = answer[j];
					break;
				case 'Y':
					k = (j + 1) % 5;
					while (S[i][k] == 'G') k = (k + 1) % 5;
					s[j] = answer[k];
					break;
				case 'B':
					s[j] = 'F';
					break;
				}
			}
			std::cout << s << '\n';
		}
	}
	else std::cout << "IMPOSSIBLE";
}