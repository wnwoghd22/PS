#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 200'001;

struct Pos {
	ll x, y;
	int i;
	ll s() const { return x * x + y * y; }
	bool operator<(const Pos& r) const { return y * r.x < r.y * x; }
	bool operator==(const Pos& r) const { return y * r.x == r.y * x; }
	friend std::istream& operator>>(std::istream& is, Pos& p) { is >> p.x >> p.y; return is; }
} O = { 0, 0 }, p[LEN];
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x); }
ll ccw(const Pos& p1, const Pos& p2, const Pos& p3) {
	ll ret = cross(p1, p2, p3);
	return ret < 0 ? -1 : !!ret;
}

bool invisible(const Pos& p1, const Pos& p2, const Pos& t) {
	return ccw(O, p1, t) <= 0 && ccw(O, p2, t) >= 0 && ccw(p1, p2, t) >= 0;
}

int N, L, R;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> p[0];
	
	p[0].i = 1;
	ll area = 0;
	for (int i = 1; i < N; ++i) {
		std::cin >> p[i];
		p[i].i = i + 1;
		area += cross(O, p[i - 1], p[i]);
	}
	area += cross(O, p[N - 1], p[0]);
	if (area > 0) std::reverse(p, p + N);
	for (int i = 1; i < N; ++i) {
		if (p[L] < p[i] || p[i] == p[L] && p[i].s() < p[L].s()) L = i;
		if (p[i] < p[R] || p[i] == p[R] && p[i].s() < p[R].s()) R = i;
	}
	std::rotate(p, p + R, p + N);
	L = (L - R + N) % N;

	// std::cout << R << ' ' << L << '\n';
	// std::cout << p[0].i << ' ' << p[L].i << '\n';

	std::vector<int> stack; // monotonic, ccw order
	stack.push_back(0);
	if (L > 1) stack.push_back(1);
	
	for (int i = 2, fv = -1, bv = -1, cw = 0; i <= L; ++i) {
		// j -> i
		ll dir = cross(O, p[i - 1], p[i]);
		ll ccw = cross(p[i - 2], p[i - 1], p[i]);

		if (!~fv && !~bv) {
			if (dir < 0) { // cw
				if (!cw && ccw < 0) {
					cw = 1;
					fv = i - 1;
					continue;
				}
				cw = 1;
				while (stack.size() && invisible(p[i - 1], p[i], p[stack.back()])) stack.pop_back();
			}
			else if (dir == 0) {
				if (p[i].s() < p[i - 1].s()) {
					if (stack.back() == i - 1) stack.pop_back();
				}
			}
			else if (dir > 0) { // ccw
				if (cw && ccw > 0) {
					cw = 0;
					bv = i - 1;
					continue;
				}
				cw = 0;
			}
			if (stack.empty() || p[stack.back()] < p[i]) stack.push_back(i);
		}
		else if (~fv) {
			if (p[fv] < p[i]) {
				cw = 0;
				fv = -1;
				if (stack.empty() || p[stack.back()] < p[i]) stack.push_back(i);
			}
		}
		else if (~bv) {
			if (p[i] < p[bv]) {
				cw = 1;
				bv = -1;
				while (stack.size() && invisible(p[i - 1], p[i], p[stack.back()])) stack.pop_back();
				if (stack.empty() || p[stack.back()] < p[i]) stack.push_back(i);
			}
		}
	}

	std::vector<int> ret;
	for (const int& i : stack) ret.push_back(p[i].i);
	std::sort(ret.begin(), ret.end());
	std::cout << ret.size() << '\n';
	for (const int& i : ret) std::cout << i << ' ';
}