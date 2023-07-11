#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 1001;
int Lx, Ly, N, lx, ly, lz, px, py, max;
int t[LEN * 4][LEN * 4];
int z[LEN * 4][LEN * 4];

void propagate(int u, int d, int l, int r, int i, int j) {
	if (z[i][j]) {
		printf("propagate %d:%d, %d:%d [%d][%d]: %d\n", u, d, l, r, i, j, z[i][j]);
		t[i][j] = z[i][j];
		if (u ^ d) z[i << 1][j] = z[i << 1 | 1][j] = z[i][j];
		if (l ^ r) z[i][j << 1] = z[i][j << 1 | 1] = z[i][j];
		z[i][j] = 0;
	}
}

void pull(int l, int r, int _u, int _d, int _l, int _r, int i, int j) {
	propagate(_u, _d, _l, _r, i, j);
	if (_r < l || r < _l) return;
	if (l <= _l && _r <= r) {
		printf("pull t[%d][%d] = %d, t[%d][%d] = %d\n", i << 1, j, t[i << 1][j], i << 1 | 1, j,  t[i << 1 | 1][j]);
		t[i][j] = std::max(t[i << 1][j], t[i << 1 | 1][j]);
		return;
	}
	int m = _l + _r >> 1;
	pull(l, r, _u, _d, _l, m, i, j << 1);
	pull(l, r, _u, _d, m + 1, _r, i, j << 1 | 1); 
	printf("pull t[%d][%d] = %d, t[%d][%d] = %d\n", i << 1, j, t[i << 1][j], i << 1 | 1, j, t[i << 1 | 1][j]);
	t[i][j] = std::max(t[i << 1][j], t[i << 1 | 1][j]);
}
void push(int l, int r, int v, int _u, int _d, int _l, int _r, int i, int j) {
	propagate(_u, _d, _l, _r, i, j);
	if (_r < l || r < _l) return;
	if (l <= _l && _r <= r) {
		t[i][j] = z[i][j] = v;
		return;
	}
	int m = _l + _r >> 1;
	push(l, r, v, _u, _d, _l, m, i, j << 1);
	push(l, r, v, _u, _d, m + 1, _r, i, j << 1 | 1);
	t[i][j] = std::max(t[i][j << 1], t[i][j << 1 | 1]);
}

void propagate_row(int l, int r, int _u, int _d, int _l, int _r, int i, int j) {
	propagate(_u, _d, _l, _r, i, j);
	if (_r < l || r < _l) return;
	if (l <= _l && _r <= r) return;
	int m = _l + _r >> 1;
	propagate_row(l, r, _u, _d, _l, m, i, j << 1);
	propagate_row(l, r, _u, _d, m + 1, _r, i, j << 1 | 1);
}

void update(int u, int d, int l, int r, int v, int _u = 0, int _d = Lx, int i = 1) {
	propagate_row(l, r, _u, _d, 0, Ly, i, 1);
	if (_d < u || d < _u) return;
	if (u <= _u && _d <= d) {
		std::cout << "update u: " << _u << ", d: " << _d << '\n';
		return push(l, r, v, _u, _d, 0, Ly, i, 1);
	}
	int m = _u + _d >> 1;
	update(u, d, l, r, v, _u, m, i << 1);
	update(u, d, l, r, v, m + 1, _d, i << 1 | 1);
	printf("pull %d ~ %d\n", _u, _d);
	pull(l, r, _u, _d, 0, Ly, i, 1);
}

int query_row(int l, int r, int _u, int _d, int _l, int _r, int i, int j) {
	propagate(_u, _d, _l, _r, i, j);
	if (_r < l || r < _l) return 0;
	if (l <= _l && _r <= r) return t[i][j];
	int m = _l + _r >> 1;
	return std::max(
		query_row(l, r, _u, _d, _l, m, i, j << 1),
		query_row(l, r, _u, _d, m + 1, _r, i, j << 1 | 1));
}

int query(int u, int d, int l, int r, int _u = 0, int _d = Lx, int i = 1) {
	if (_d < u || d < _u) return 0;
	propagate_row(l, r, _u, _d, 0, Ly, i, 1);
	if (_u ^ _d) pull(l, r, _u, _d, 0, Ly, i, 1);
	if (u <= _u && _d <= d) {
		std::cout << "query u: " << _u << ", d: " << _d << ", i: " << i << '\n';
		int cur = query_row(l, r, _u, _d, 0, Ly, i, 1);
		std::cout << cur << '\n';
		return cur;
	}
	int m = _u + _d >> 1;
	return std::max(
		query(u, d, l, r, _u, m, i << 1),
		query(u, d, l, r, m + 1, _d, i << 1 | 1));
}

int main() {
	// freopen("input.txt", "r", stdin);
	// std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> Lx >> Ly >> N;
	while (N--) {
		std::cin >> lx >> ly >> lz >> px >> py;
		max = query(px, px + lx - 1, py, py + ly - 1);
		std::cout << max << '\n';
		max += lz;
		update(px, px + lx - 1, py, py + ly - 1, max);
	}
	max = query(0, Lx, 0, Ly);
	std::cout << max;
}