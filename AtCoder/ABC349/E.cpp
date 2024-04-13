#include <iostream>

typedef long long ll;
ll A[3][3];

int cases[9][9] = {
	-1, 1, 1, 1, 1, -1, -1, -1, 1,

};

int main() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cin >> A[i][j];
		}
	}

}