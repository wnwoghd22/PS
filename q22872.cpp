#include <iostream>

const int LEN = 980403;

int N, i;
struct CMD { int a, b; } cmd[LEN];

void f(int l, int m, int r, int s, int e) {
	if (s == e) {
		cmd[i++] = { l, r };
		return;
	}
	if (s == 1) {
		f(l, r, m, s + 1, e);
		f(l, m, r, 1, 1);
		f(m, l, r, s + 1, e);
	}
	else {
		 
	}
}

int main() {
	std::cin >> N;
	f(1, 2, 3, 1, N);
	for (int j = 0; j < i; ++j) std::cout << cmd[j].a << ' ' << cmd[j].b << '\n';
}