#include <iostream>
#include <algorithm>

struct E { int i, v, o; }; // index, value, order
int N, A;
E a[50];
bool I(const E& l, const E& r) { return l.i < r.i; }
bool V(const E& l, const E& r) { if (l.v != r.v) return l.v < r.v; return I(l, r); }

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		a[i] = { i, A, 0 };
	}
	std::sort(a, a + N, V);
	for (int i = 0; i < N; ++i) a[i].o = i;
	std::sort(a, a + N, I);
	for (int i = 0; i < N; ++i) std::cout << a[i].o << ' ';
}