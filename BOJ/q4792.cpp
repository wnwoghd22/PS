#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 1001;

struct Edge { int u, v; } red[LEN * LEN / 2], blue[LEN * LEN / 2];
int sp_r, sp_b;
int N, M, K, p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}
char C;
int f, t, max, min, cc;

int solve() {
	sp_r = sp_b = 0;
	std::cin >> N >> M >> K;
	if (!N && !M && !K) return 0;
	while (M--) {
		std::cin >> C >> f >> t;
		if (C == 'R') red[sp_r++] = { f, t };
		if (C == 'B') blue[sp_b++] = { f, t };
	}
	
	cc = 0;
	memset(p, -1, sizeof p);
	for (int i = 0; i < sp_b; ++i) join(blue[i].u, blue[i].v) ? ++cc : 0;
	max = cc;

	cc = N;
	memset(p, -1, sizeof p);
	for (int i = 0; i < sp_r; ++i) join(red[i].u, red[i].v) ? --cc : 0;
	min = cc - 1;

	std::cout << (min <= K && K <= max ? 1 : 0) << '\n';
	return 1;
}

int main() { freopen("input.txt", "r", stdin); while (solve()); }