#include <iostream>

const int LEN = 3'000'001;

int len, u[LEN], v[LEN];

inline void move(int s, int e) { u[len] = s; v[len] = e; len++; }

void hanoi(int n, int s, int m, int e, int state = -1) {
	if (!~state) {
		hanoi(n - 1, s, e, m, 1 << s);
		move(s, e);
		hanoi(n - 1, m, s, e, 1 << e);
		return;
	}
	if (n <= 0) return;
	if (n == 1) {
		move(s, e);
		return;
	}
	if (!!(state & 1 << s) != !!(state & 1 << e)) {
		hanoi(n - 2, s, e, m, state);
		move(s, e); move(s, e);
		hanoi(n - 2, m, s, e, state);
	}
	else if (!(state & 1 << s) && !(state & 1 << e)) {
		if (n == 2) {
			move(s, m); move(s, e); move(m, e);
			return;
		}
		hanoi(n - 2, s, m, e, state);
		move(s, m); move(s, m);
		hanoi(n - 2, e, m, s, state);
		move(m, e); move(m, e);
		hanoi(n - 2, s, m, e, state);
	}
}


int main() {
	int N;
	std::cin >> N;
	hanoi(N, 1, 2, 3);
	std::cout << len << '\n';
	for (int i = 0; i < len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
}