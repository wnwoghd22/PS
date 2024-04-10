#include <iostream>
#include <string>

const int RAINBOW = 19022146;
int N, mask, MASK;
std::string S;

int main() {
	std::cin >> N >> S;
	for (const char& c : S) {
		if (c >= 'a' && c <= 'z') mask |= 1 << c - 'a';
		if (c >= 'A' && c <= 'Z') MASK |= 1 << c - 'A';
	}
	if (((mask & RAINBOW) == RAINBOW) && ((MASK & RAINBOW) == RAINBOW)) std::cout << "YeS";
	else if ((mask & RAINBOW) == RAINBOW) std::cout << "yes";
	else if ((MASK & RAINBOW) == RAINBOW) std::cout << "YES";
	else std::cout << "NO!";
}