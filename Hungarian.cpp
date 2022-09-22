#include <iostream>
#include <algorithm>
#include <cstring>

const int INF = 1e9;
const int MAX = 500;

int cost[MAX][MAX];
int N, max_match;

int lx[MAX], ly[MAX]; // labels of X, Y
int xy[MAX], yx[MAX]; // matched vertices (x -> y, y -> x)
bool S[MAX], T[MAX];
int slack[MAX];
int slackx[MAX];
int prev[MAX];

int q[MAX], qw, qr;

void init_labels() {
	memset(lx, 0, sizeof lx);
	memset(ly, 0, sizeof ly);
	for (int x = 0; x < N; ++x)
		for (int y = 0; y < N; ++y)
			lx[x] = std::max(lx[x], cost[x][y]);
}

void update_labels() {
	int x, y, delta = INF;
	for (y = 0; y < N; ++y)
		if (!T[y]) delta = std::min(delta, slack[y]);

	for (x = 0; x < N; ++x)
		if (S[x]) lx[x] -= delta;
	for (y = 0; y < N; ++y)
		if (T[y]) ly[y] += delta;

	for (y = 0; y < N; ++y)
		if (!T[y]) slack[y] -= delta;
}

void add_to_tree(int x, int prevx) {
	S[x] = true; // add x to S
	prev[x] = prevx;
	for (int y = 0; y < N; ++y) {
		if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
			slack[y] = lx[x] + ly[y] - cost[x][y];
			slackx[y] = x;
		}
	}
}

void augment() {
	if (max_match == N) return;

	int x, y, root;
	memset(q, 0, sizeof q), qw = qr = 0;
	memset(S, 0, sizeof S);
	memset(T, 0, sizeof T);
	memset(prev, -1, sizeof prev);

	for (x = 0; x < N; ++x) { // find root
		if (xy[x] == -1) {
			q[qw++] = root = x;
			prev[x] = -2;
			S[x] = true;
			break;
		}
	}

	for (y = 0; y < N; ++y) { // initialize slack tree
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}

	while (true) {
		while (qr < qw) {
			x = q[qr++]; // current vertex
			for (y = 0; y < N; ++y) {
				if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
					if (yx[y] == -1) break; // exposed Y -> augment path

					T[y] = true;
					q[qw++] = yx[y];

					add_to_tree(yx[y], x);
				}
			}
			if (y < N) break; // augment path found
		}
		if (y < N) break; // augment path found

		update_labels(); // augment path not found, improve labeling

		memset(q, 0, sizeof q), qw = qr = 0;

		for (y = 0; y < N; ++y) {
			if (!T[y] && !slack[y]) {
				if (yx[y] == -1) { // exposed Y -> augment path
					x = slackx[y];
					break;
				}

				T[y] = true;
				if (!S[yx[y]]) {
					q[qw++] = yx[y];
					add_to_tree(yx[y], slackx[y]);
				}
			}
		}
		if (y < N) break;
	}

	if (y < N) {
		++max_match;

		for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
			ty = xy[cx];
			yx[cy] = cx;
			xy[cx] = cy;
		}
		augment();
	}
}

int Hungarian() {
	int ret = 0;
	max_match = 0;
	memset(xy, -1, sizeof xy);
	memset(yx, -1, sizeof yx);

	init_labels();
	augment();

	for (int x = 0; x < N; ++x)
		ret += cost[x][xy[x]];

	return ret;
}

int main() {
	std::cin >> N;

	for (int x = 0; x < N; ++x) {
		for (int y = 0; y < N; ++y) {
			std::cin >> cost[x][y];
			cost[x][y] *= -1;
		}
	}

	std::cout << -Hungarian();
}