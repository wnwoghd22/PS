#include <iostream>

const int dx[4] = { 1, 0, -1, 0 }; // R, U, L, D
const int dy[4] = { 0, 1, 0, -1 };

int L, N;

struct Seg {
	int l, r, u, d;
	bool intersest(const Seg& o) const {
		if (l == r && o.l == o.r) { // vertical
			return o.d <= d && d <= o.u ||
				o.d <= u && u <= o.u;
		}
		if (d == u && o.d == o.u) { // horizontal
			return o.l <= l && l <= o.r ||
				o.l <= r && r <= o.r;
		}
		return o.l <= l && r <= o.r && d <= o.d && o.u <= u ||
			l <= o.l && o.r <= r && o.d <= d && u <= o.u;
	}
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> L >> N;

}