#include <iostream>
#include <vector>

typedef long long int ll;

ll N, K, R, Q;

int dir[200'001];
int x[200'001];
int y[200'001];

inline bool inside(ll x1, ll y1, ll x2, ll y2, ll r) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= r * r;
}
inline int check(int x1, int y1, int x2, int y2, int d) {
	switch (d) {
	case 2:
		if (x1 == x2) return 0;
		if (x1 > x2) return 1;
		else return -1;
	case -2:
		if (x1 == x2) return 0;
		if (x1 < x2) return 1;
		else return -1;
	case 1:
		if (y1 == y2) return 0;
		if (y1 < y2) return 1;
		else return -1;
	case -1:
		if (y1 == y2) return 0;
		if (y1 > y2) return 1;
		else return -1;
	}
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> K >> R >> Q;

	for (int di, i, k = 0; k < K; ++k) {
		std::cin >> i;
		std::cin >> x[i] >> y[i];
		if (k >= 1) {
			int d = i - di;
			int dx = (x[i] - x[di]) / d;
			int dy = (y[i] - y[di]) / d;
			dir[di] = dx + 2 * dy;
			for (int j = di + 1; j < i; ++j) {
				dir[j] = dx + 2 * dy;
				x[j] = x[j - 1] + dx;
				y[j] = y[j - 1] + dy;
			}
		}
		di = i;
	}
	dir[N] = dir[N - 1];

	int J, X, Y;
	while (Q--) {
		std::cin >> J >> X >> Y;
		if (inside(X, Y, x[J], y[J], R)) {
			switch (check(X, Y, x[J], y[J], dir[J])) {
			case -1:
				std::cout << "safe\n";
				break;
			case 1:
				std::cout << "unsafe\n";
				break;
			case 0:
				std::cout << "gori\n";
			}
		}
		else {
			std::cout << "gori\n";
		}
	}
}