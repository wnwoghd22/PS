#include <iostream>

int N, J, ret;
char S[101];

int main() {
	std::cin >> J >> N; std::cin.ignore();
	for (int i = 0, j; i < N; ++i) {
		std::cin.getline(S, 101);
		j = 0;
		for (int k = 0; S[k]; ++k) {
			if (S[k] >= 'A' && S[k] <= 'Z') j += 4;
			if (S[k] >= 'a' && S[k] <= 'z') j += 2;
			if (S[k] >= '0' && S[k] <= '9') j += 2;
			if (S[k] == ' ') j += 1;
		}
		if (j <= J) ret++;
	}
	std::cout << ret;
}