#include <iostream>
#include <algorithm>

const int INF = 1e9;

int N;
bool l, r, u, d;
int L, R, U, D;
int x, y;
char dir;

int main() {
	std::cin >> N;
	L = D = -INF;
	R = U = INF;
	while (N--) {
		std::cin >> x >> y >> dir;
		switch (dir) {
		case 'L':
			l = 1;
			R = std::min(R, x - 1);
			break;
		case 'R':
			r = 1;
			L = std::max(L, x + 1);
			break;
		case 'U':
			u = 1;
			D = std::max(D, y + 1);
			break;
		case 'D':
			d = 1;
			U = std::min(U, y - 1);
			break;
		}
	}
	if (l & r & u & d) std::cout << (long long)(R - L + 1) * (U - D + 1);
	else std::cout << "Infinity";
}