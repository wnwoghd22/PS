#include <iostream>

int mat[5][5] = {
	0, 1, 2, 2, 1,
	1, 0, 1, 2, 2,
	2, 1, 0, 1, 2,
	2, 2, 1, 0, 1,
	1, 2, 2, 1, 0
};

std::string S, T;

int main() {
	std::cin >> S >> T;
	std::cout << (mat[S[0] - 'A'][S[1] - 'A'] == mat[T[0] - 'A'][T[1] - 'A'] ? "Yes" : "No");
}