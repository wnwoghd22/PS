#include <iostream>
#include <cstring>

const int LEN = 4e5 + 1;

int H, W, Q;
bool checked[LEN];

struct DisjointSet {
	int p[LEN];
	int find(int i) {
		// std::cout << "find: " << i << ' ' << p[i] << '\n';
		return p[i] < 0 ? i : p[i] = find(p[i]);
	}
	int join(int a, int b) {
		// std::cout << "join: " << a << ' ' << b << '\n';
		a = find(a), b = find(b);
		// std::cout << "join: " << a << ' ' << b << '\n';
		if (a == b) return 0;
		p[a] += p[b]; p[b] = a;
		return 1;
	}
} L, R, U, D;

void f(int r, int c) {
	// std::cout << "f(" << r << ", " << c << ")\n";
	int x = r * W + c;
	int i, j;

	// std::cout << "f_L\n";
	int _l = L.find(x);
	if (_l - 1 >= r * W && checked[_l - 1]) {
		L.join(_l - 1, _l);
		R.join(_l, _l - 1);
	}

	// std::cout << "f_R\n";
	int _r = R.find(x);
	if (_r + 1 < (r + 1) * W && checked[_r + 1]) {
		R.join(_r + 1, _r);
		L.join(_r, _r + 1);
	}

	// std::cout << "f_U\n";
	int _u = U.find(x);
	if (_u - W >= 0 && checked[_u - W]) {
		U.join(_u - W, _u);
		D.join(_u, _u - W);
	}

	// std::cout << "f_D\n";
	int _d = D.find(x);
	if (_d + W < W * H && checked[_d + W]) {
		D.join(_d + W, _d);
		U.join(_d, _d + W);
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> H >> W >> Q;
	memset(L.p, -1, sizeof L.p);
	memset(R.p, -1, sizeof R.p);
	memset(U.p, -1, sizeof U.p);
	memset(D.p, -1, sizeof D.p);

	int ret = H * W;
	for (int q = 0, x, y, r, c; q < Q; ++q) {
		std::cin >> r >> c;
		r--; c--;
		x = r * W + c;
		// std::cout << "index: " << x << '\n';
		if (!checked[x]) {
			ret -= 1;
			checked[x] = 1;
			f(r, c);
		}
		else {
			// std::cout << "connect\n";
			// std::cout << "L\n";
			int _l = L.find(x) - 1;
			if (_l >= r * W) {
				ret -= 1;
				checked[_l] = 1;
				L.join(_l, x);
				R.join(x, _l);
				// std::cout << "L_f\n";
				f(_l / W, _l % W);
			}

			// std::cout << "R\n";
			int _r = R.find(x) + 1;
			if (_r < (r + 1) * W) {
				ret -= 1;
				checked[_r] = 1;
				R.join(_r, x);
				L.join(x, _r);
				// std::cout << "R_f\n";
				f(_r / W, _r % W);
			}

			// std::cout << "U\n";
			int _u = U.find(x) - W;
			if (_u >= 0) {
				ret -= 1;
				checked[_u] = 1;
				U.join(_u, x);
				D.join(x, _u);
				// std::cout << "U_f\n";
				f(_u / W, _u % W);
			}

			// std::cout << "D\n";
			int _d = D.find(x) + W;
			if (_d < W * H) {
				ret -= 1;
				checked[_d] = 1;
				D.join(_d, x);
				U.join(x, _d);
				// std::cout << "D_f\n";
				f(_d / W, _d % W);
			}
		}
	}
	std::cout << ret;
}