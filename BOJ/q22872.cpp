#include <iostream>

const int LEN = 1'000'001;

int len, u[LEN], v[LEN];

inline void move(int s, int e) { u[len] = s; v[len] = e; len++; }
inline void split(int s, int m, int e) { move(s, e); move(s, m); move(e, s); move(m, e); move(s, e); }

void hanoi(int n, int s, int m, int e, int state = 0) {
	if (n <= 0) return;
	if (n == 1) move(s, e);
	else if (((state >> s) & 1) ^ ((state >> e) & 1)) { // 1 -> 0, 0 -> 1, normal cost
		hanoi(n - 2, s, e, m, state);
		move(s, e); move(s, e);
		hanoi(n - 2, m, s, e, state);
	}
	else if (((state >> s) & 1) ^ ((state >> m) & 1)) { // 0 -> 1 -> 0, 1 -> 0 -> 1, split
		if (n == 2) {
			move(s, m); move(s, e); move(m, e);
			return;
		}
		if (n == 3) {
			move(s, m);
			split(s, m, e);
			move(m, e);
			return;
		}
		else if (n == 4) {
			move(s, m); move(s, e); move(s, e); move(s, m);
			split(e, m, s);
			move(m, e); move(s, e); move(s, e); move(m, e);
			return;
		}
		hanoi(n - 3, s, e, m, state ^ (1 << s));
		move(s, e); move(s, e);
		hanoi(n - 4, m, s, e, state ^ (1 << s | 1 << m));
		move(s, m);

		hanoi(n - 2, e, m, s, state);

		move(m, e);
		hanoi(n - 4, s, e, m, state ^ (1 << m | 1 << e));
		move(s, e); move(s, e);
		hanoi(n - 3, m, s, e, state ^ (1 << e));
	}
	else {
		hanoi(n - 1, s, e, m, state ^ (1 << s));
		move(s, e);
		hanoi(n - 1, m, s, e, state ^ (1 << e));
	}
}

int main() {
	int N;
	std::cin >> N;
	hanoi(N, 1, 2, 3);
	std::cout << len << '\n';
	for (int i = 0; i < len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';
}