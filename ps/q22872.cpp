#include <iostream>

const int LEN = 1'000'001;

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
		if ((state & 1 << s) && (state & 1 << e)) move(s, m);
		move(s, e);
		if (!state) move(m, e); 
		return;
	}
	else if (!state) { // splited
		if (n == 2) {
			move(s, e); move(m, e); move(s, e);
			return;
		}
		hanoi(n - 2, s, e, m, 0);
		move(s, e);
		hanoi(n - 3, m, e, s, 1 << e);
		move(m, e); move(m, e);
		hanoi(n - 2, s, m, e, 1 << m);
	}
	else if (!!(state & 1 << s) != !!(state & 1 << e)) { // 1 -> 0, 0 -> 1, normal cost
		hanoi(n - 2, s, e, m, state);
		move(s, e); move(s, e);
		hanoi(n - 2, m, s, e, state);
	}
	else if (!(state & 1 << s) && !(state & 1 << e)) { // 0 -> 0, need to split
		if (n == 2) {
			move(s, m); move(s, e); move(m, e);
			return;
		}
		hanoi(n - 1, s, e, m, state ^ 1 << s);
		n % 4 < 2 ? move(s, e) : move(e, s);
		hanoi(n - 1, m, s, e, state ^ 1 << m);
	}
	else if ((state & 1 << s) && (state & 1 << e)) { // 1 -> 1, state chenaged
		if (n == 2) {
			move(s, e); move(s, m); move(s, e);
			return;
		}
		hanoi(n - 2, s, m, e, state ^ 14);
		move(s, m); move(s, m);
		hanoi(n - 3, e, s, m, state ^ (1 << e));
		move(s, e);
		hanoi(n - 2, m, s, e, state ^ (1 << s | 1 << m));
	}
}

int main() {
	int N;
	std::cin >> N;
	hanoi(N, 1, 2, 3);
	std::cout << len << '\n';
	for (int i = 0; i < len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
}