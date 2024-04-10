#include <iostream>

int main() {
	int N;
	std::cin >> N;

	std::cout << "int a;\n";
	std::cout << "int *ptr = &a;\n";

	if (N >= 2)
		std::cout << "int **ptr2 = &ptr;\n";

	for (int i = 3; i <= N; ++i) {
		std::cout << "int " << std::string(i, '*') << "ptr" << i << " = " << "&ptr" << i - 1 << ";\n";
	}
}