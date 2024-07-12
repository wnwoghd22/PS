#include <iostream>

const int LEN = 3'000'001;

int len, u[LEN], v[LEN];

void hanoi(int n, int s, int m, int e, int state = -1) {
	if (!~state) {
		hanoi(n - 1, s, e, m, 1 << s);
		u[len] = s; v[len] = e; len++;
		hanoi(n - 1, m, s, e, 1 << e);
		return;
	}
	if (n <= 0) return;
	if (n == 1) {
		u[len] = s; v[len] = e; len++;
		return;
	}
	if (!!(state & 1 << s) != !!(state & 1 << e)) {
		hanoi(n - 2, s, e, m, state);
		u[len] = s; v[len] = e; len++;
		u[len] = s; v[len] = e; len++;
		hanoi(n - 2, m, s, e, state);
	}
	else if (!(state & 1 << s) && !(state & 1 << e)) {
		if (n == 2) {
			u[len] = s; v[len] = m; len++;
			u[len] = s; v[len] = e; len++;
			u[len] = m; v[len] = e; len++;
			return;
		}
		// ???
	}
	else if (state & 1 << s) {
	}
	else if (state & 1 << e) {

	}
}


int main() {
	int N;
	std::cin >> N;
	hanoi(N, 1, 2, 3);
	std::cout << len << '\n';
	// for (int i = 0; i < len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
}