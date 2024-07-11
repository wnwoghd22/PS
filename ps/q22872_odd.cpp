#include <iostream>

const int LEN = 1'000'001;

int len, u[LEN], v[LEN];

void hanoi(int n, int s, int m, int e, int odd) {
	if (n & 1) {
		hanoi(n - 1, s, e, m, odd);
		u[len] = s; v[len] = e; len++;
		hanoi(n - 1, m, s, e, odd = e);
		return;
	}
	if (n <= 0) return;
	if (n == 2) {
		if (s == odd || e == odd) {
			u[len] = s; v[len] = e; len++;
			u[len] = s; v[len] = e; len++;
		}
		else {
			u[len] = s; v[len] = m; len++;
			u[len] = s; v[len] = e; len++;
			u[len] = m; v[len] = e; len++;
		}
		return;
	}
	if (s == odd || e == odd) {
		hanoi(n - 2, s, e, m, odd);
		u[len] = s; v[len] = e; len++;
		u[len] = s; v[len] = e; len++;
		hanoi(n - 2, m, s, e, odd);
	}
	else {
		hanoi(n - 2, s, m, e, odd);
		u[len] = s; v[len] = m; len++;
		u[len] = s; v[len] = m; len++;
		hanoi(n - 2, e, m, s, odd);
		u[len] = m; v[len] = e; len++;
		u[len] = m; v[len] = e; len++;
		hanoi(n - 2, s, m, e, odd);
	}
}


int main() {
	int N;
	std::cin >> N;
	hanoi(N, 1, 2, 3, 1);
	std::cout << len << '\n';
	// for (int i = 0; i < len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
}