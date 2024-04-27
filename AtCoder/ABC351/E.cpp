#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 4e5;

int N;

struct Space {
	int C;
	int X;
	std::map<int, int> order;

	struct Pos {
		int x, y;
		int f() const { return y - x; }
		int g() const { return x + y; }
		bool operator<(const Pos& r) const {
			if (f() == r.f()) return x > r.x;
			return f() > r.f();
		}
	} arr[LEN];

	struct SegSum {
		ll t[LEN << 2];
		void update(int x, ll d, int s, int e, int i = 1) {
			if (x < s || e < x) return;
			if (s == e) {
				t[i] += d;
				return;
			}
			int m = s + e >> 1;
			update(x, d, s, m, i << 1);
			update(x, d, m + 1, e, i << 1 | 1);
			t[i] = t[i << 1] + t[i << 1 | 1];
		}
		ll get(int l, int r, int s, int e, int i = 1) {
			if (r < s || e < l) return 0;
			if (l <= s && e <= r) return t[i];
			int m = s + e >> 1;
			return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
		}
	} sumX, sumY, cnt;

	int el[LEN];

	void push(int x, int y) {
		arr[C] = { x, y };
		el[C] = x + y;
		C++;
	}

	void init() {
		std::sort(arr, arr + C);
		std::sort(el, el + C);
		X = 1;
		order[el[0]] = 1;
		for (int i = 1; i < C; ++i) {
			if (el[i] != el[i - 1]) X++;
			order[el[i]] = X;
		}
	}

	ll solve() {
		ll ret = 0;
		for (int i = 0; i < C; ++i) {
			int ord = order[arr[i].g()];
			ll y = sumY.get(ord, X, 1, X);
			ll x = sumX.get(1, ord - 1, 1, X);
			ll cy = cnt.get(ord, X, 1, X);
			ll cx = cnt.get(1, ord - 1, 1, X);
			ll SY = y - arr[i].y * cy;
			ll SX = arr[i].x * cx - x;
			ret += SY + SX;

			sumY.update(ord, arr[i].y, 1, X);
			sumX.update(ord, arr[i].x, 1, X);
			cnt.update(ord, 1, 1, X);
		}
		return ret;
	}
} even, odd;


int A[LEN], order[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, x, y; i < N; ++i) {
		std::cin >> x >> y;
		if ((x + y) & 1) {
			odd.push(x, y);
		}
		else {
			even.push(x, y);
		}
	}
	odd.init();
	even.init();

	ll ret = odd.solve() + even.solve();

	std::cout << ret;
}