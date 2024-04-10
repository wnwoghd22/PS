#include <iostream>

class Gear {
private:
	std::string pol;
	int state;
	void rotateL(int dir) {
		if (left && left->get3() != get9()) left->rotateL(-dir);

		state = (state + dir) % 8;
		if (state < 0) state = 7;
	}
	void rotateR(int dir) {
		if (right && right->get9() != get3()) right->rotateR(-dir);

		state = (state + dir) % 8;
		if (state < 0) state = 7;
	}
public:
	Gear *left, *right;
	Gear(std::string s) : pol(s), state(0), left(0), right(0) {}
	char get12() { return pol[state]; }
	char get3() { return pol[(state + 2) % 8]; }
	char get9() { return pol[(state + 6) % 8]; }

	void rotate(int dir) {
		if (left && left->get3() != get9()) left->rotateL(-dir);
		if (right && right->get9() != get3()) right->rotateR(-dir);

		state = (state + dir) % 8;
		if (state < 0) state = 7;
	}
};

Gear* A[4];
void simulate(int n, int dir) { A[n - 1]->rotate(-dir); }

int main() {
	for (int i = 0; i < 4; ++i) {
		std::string s;
		std::cin >> s;
		A[i] = new Gear(s);
	}
	A[0]->right = A[1];
	A[1]->left = A[0], A[1]->right = A[2];
	A[2]->left = A[1], A[2]->right = A[3];
	A[3]->left = A[2];

	int K, n, dir;
	std::cin >> K;
	while (K--) {
		std::cin >> n >> dir;
		simulate(n, dir);
	}

	for (K = 0, n = 1, dir = 0; dir < 4; ++dir, n <<= 1) {
		K += A[dir]->get12() == '1' ? n : 0;
	}
	std::cout << K;
}