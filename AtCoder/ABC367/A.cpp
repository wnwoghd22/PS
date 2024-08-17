#include <iostream>

int main() {
	int A, B, C;
	std::cin >> A >> B >> C;
	bool ans;
	if (B < C) {
		if (A >= B && A < C) ans = false;
		else ans = true;
	}
	else {
		if (A >= B || A < C) ans = false;
		else ans = true;
	}
	std::cout << (ans ? "Yes" : "No");
}