#include <iostream>

int A[10], sum;

int main() {
	std::string s;
	std::cin >> s;
	for (const char& c : s) sum += c - '0', ++A[c - '0'];
	if (sum % 3 || !A[0]) std::cout << -1;
	else for (int i = 9; i >= 0; --i) while (A[i]--) std::cout << i;
}