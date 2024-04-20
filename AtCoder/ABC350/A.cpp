#include <iostream>

char S[7];

int main() {
	std::cin >> S;
	int n = (S[3] - '0') * 100 + (S[4] - '0') * 10 + S[5] - '0';
	if (n == 316 || n < 1 || n > 349) std::cout << "No";
	else std::cout << "Yes";
}