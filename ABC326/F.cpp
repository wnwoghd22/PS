#include <iostream>
#include <vector>
#include <map>

int N, X, Y;
std::vector<int> A[2];
std::map<int, int> m[4];

void f(std::map<int, int>& m, const std::vector<int>& a, int s, int i, int e, int bit, int dist) {
	if (i == e) {
		m[dist] = bit;
		return;
	}
	f(m, a, s, i + 1, e, bit, dist - a[i]);
	f(m, a, s, i + 1, e, bit | 1 << i - s, dist + a[i]);
}

int b0, b1, b2, b3;
int f1, f2;

int main() {
	std::cin >> N >> X >> Y;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> a;
		A[i & 1].push_back(a);
	}
	for (const int& e : A[0]) std::cout << e << ' '; std::cout << '\n';
	for (const int& e : A[1]) std::cout << e << ' '; std::cout << '\n';
	for (int i = 0; i <= 1; ++i) {
		std::cout << A[i].size() << '\n';
		if (A[i].size())
			f(m[i * 2], A[i], 0, 0, (A[i].size() + 1) / 2, 0, 0);
		if (A[i].size() > 1)
			f(m[i * 2 + 1], A[i], (A[i].size() + 1) / 2, (A[i].size() + 1) / 2, A[i].size(), 0, 0);
	}
	if (!m[1].size()) m[1][0] = 0;
	if (!m[2].size()) m[2][0] = 0;
	if (!m[3].size()) m[3][0] = 0;
	
	for (int i = 0; i < 4; ++i) {
		std::cout << "map " << i << ' ';
		for (auto&[k, v] : m[i]) std::cout << k << ' ';
		std::cout << '\n';
	}
	for (auto&[k, v] : m[0]) {
		if (m[1].find(Y - k) != m[1].end()) {
			f1 = 1;
			b0 = v; b2 = m[1][Y - k];
			break;
		}
	}
	for (auto&[k, v] : m[2]) {
		if (m[3].find(X - k) != m[3].end()) {
			f2 = 1;
			b1 = v; b3 = m[3][X - k];
			break;
		}
	}
	if (f1 && f2) {
		int dir = 0;
		std::cout << b0 << b1 << b2 << b3;

		std::cout << "Yes\n";
	}
	else std::cout << "No";
}
