#include <iostream>

int mat[2][2];

void operate() {
	int temp = mat[0][0];
	mat[0][0] = mat[1][0];
	mat[1][0] = mat[1][1];
	mat[1][1] = mat[0][1];
	mat[0][1] = temp;
}
bool check() {return mat[0][1] > mat[0][0] && mat[1][1] > mat[1][0] && mat[1][0] > mat[0][0] && mat[1][1] > mat[0][1]; }

bool is_beautiful() {
	if (check()) return true;
	operate();
	if (check()) return true;
	operate();
	if (check()) return true;
	operate();
	return check();
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::cin >> mat[0][0] >> mat[0][1] >> mat[1][0] >> mat[1][1];
		std::cout << (is_beautiful() ? "YES\n" : "NO\n");
	}
}