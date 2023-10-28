#include <iostream>

int main() {
	int A, B;
	std::cin >> A >> B;
	if (B >= A - 3 && B <= A + 2) std::cout << "Yes";
	else std::cout << "No";

}