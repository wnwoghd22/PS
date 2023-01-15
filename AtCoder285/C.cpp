#include <iostream>
#include <cmath>

typedef long long int ll;

int main() {
	std::string s;
	std::cin >> s;
	ll x = 0;
	for (const char& c : s) {
		x = x * 26 + (c - 'A' + 1);
	}
	std::cout << x;
}