#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 200'001;

struct Pos {
	ll x, y;
	ll s() const { return x * x + y * y; }
	bool operator<(const Pos& r) const { return y * r.x < r.y * x; }
	bool operator==(const Pos& r) const { return y * r.x == r.y * x; }
	friend std::istream& operator>>(std::istream& is, Pos& p) { is >> p.x >> p.y; return is; }
} O = { 0, 0 }, p[LEN];
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x); }

int N, L, R;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> p[0];
	for (int i = 0; i < N; ++i) {
		std::cin >> p[i];
		if (p[L] < p[i] || p[i] == p[L] && p[i].s() < p[L].s()) L = i;
		if (p[i] < p[R] || p[i] == p[R] && p[i].s() < p[R].s()) R = i;
	}

	std::vector<int> stack; // monotonic, ccw order
	stack.push_back(R);

	for (int i = (R + 1) % N, j = R, visible = 1; i != L; ++i %= N, ++j %= N) {
		// j -> i
		ll dir = cross(O, p[j], p[i]);

		if (visible) {

		}
		else {
			if (p[stack.back()] < p[i]) {
				// ???
			}
		}


	}

	stack.push_back(L);
	std::sort(stack.begin(), stack.end());
	for (const int& i : stack) std::cout << i << ' ';
}