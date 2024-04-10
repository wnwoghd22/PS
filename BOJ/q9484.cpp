#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2001;
const ll INF = 1e17;

struct Slope {
	int u, v;
	ll dx, dy;
	bool operator<(const Slope& r) const { return dy * r.dx < r.dy * dx; }
	bool operator==(const Slope& r) const { return dy * r.dx == r.dy * dx; }
} slopes[LEN * LEN];
int M;

struct Pos {
	ll x, y;
	int i;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
} pos[LEN]; 
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x); }

int N, idx[LEN], ord[LEN];
ll min, max;

bool solve() {
	std::cin >> N;
	if (!N) return 0;
	M = 0;
	for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y;
	std::sort(pos, pos + N);
	min = INF; max = 0;
	for (int i = 0; i < N; ++i) {
		pos[i].i = i;
		if (i < N - 2 && pos[i].x == pos[i + 1].x) 
			min = std::min(min, abs(cross(pos[i], pos[i + 1], pos[i + 2])));

		for (int j = i + 1; j < N; ++j) {
			int dx = pos[i].x - pos[j].x;
			int dy = pos[i].y - pos[j].y;
			if (!dx) continue;
			slopes[M++] = { i, j, dx, dy };
		}
	}
	std::stable_sort(slopes, slopes + M);
	for (int i = 0; i < N; ++i) {
		idx[pos[i].i] = i;
		ord[i] = pos[i].i;
	}

	for (int i = 0, j; i < M; i = j) {
		j = i;
		while (j < M && slopes[i] == slopes[j]) {
			int u = slopes[j].u, v = slopes[j].v;
			int x = idx[u], y = idx[v];

			if (x > y) std::swap(x, y);

			if (x > 0) {
				min = std::min(min, abs(cross(pos[u], pos[v], pos[ord[x - 1]])));
				max = std::max(max, abs(cross(pos[u], pos[v], pos[ord[0]])));
			}
			if (y < N - 1) {
				min = std::min(min, abs(cross(pos[u], pos[v], pos[ord[y + 1]])));
				max = std::max(max, abs(cross(pos[u], pos[v], pos[ord[N - 1]])));
			}

			std::swap(idx[u], idx[v]);
			std::swap(ord[x], ord[y]);

			++j;
		}
	}
	std::cout << min / 2 << '.' << (min & 1) * 5 << ' ';
	std::cout << max / 2 << '.' << (max & 1) * 5 << '\n';
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	while (solve());
}