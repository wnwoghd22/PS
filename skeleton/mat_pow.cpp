#include <iostream>

typedef long long ll;
const ll MOD = 1000;

struct M {
	int** m;
	int r, c;
	M(int r, int c) : r(r), c(c) {
		m = new int*[r];
		for (int i = 0; i < r; ++i) {
			m[i] = new int[c];
			for (int j = 0; j < c; ++j)
				m[i][j] = 0;
		}
	}
	M(const M& R) : r(R.r), c(R.c) {
		m = new int*[r];
		for (int i = 0; i < r; ++i) {
			m[i] = new int[c];
			for (int j = 0; j < c; ++j)
				m[i][j] = R.m[i][j];
		}
	}
	M& operator=(const M& R) {
		if (this == &R) return *this;
		for (int i = 0; i < r; ++i)
			delete[] m[i];
		delete[] m;
		r = R.r; c = R.c;
		m = new int*[r];
		for (int i = 0; i < r; ++i) {
			m[i] = new int[c];
			for (int j = 0; j < c; ++j)
				m[i][j] = R.m[i][j];
		}
		return *this;
	}

	~M() {
		// std::cout << "destruct!\n";
		for (int i = 0; i < r; ++i)
			delete[] m[i];
		delete[] m;
	}
	M operator*(const M& R) const {
		M p(r, R.c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < R.c; ++j) {
				for (int k = 0; k < c; ++k) {
					p.m[i][j] += m[i][k] * R.m[k][j];
					p.m[i][j] %= MOD;
				}
			}
		}
		return p;
	}
};

int main() {
	int n;
	ll B;
	std::cin >> n >> B;

	M A(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			std::cin >> A.m[i][j];
	}
	M C(n, n);
	for (int i = 0; i < n; ++i) C.m[i][i] = 1;

	while (B--) {
		C = C * A;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			std::cout << C.m[i][j] << ' ';
		std::cout << '\n';
	}
}