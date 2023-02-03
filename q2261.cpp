#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long int ll;
const int LEN = 100'000;
const int INF = 1e17;
struct pos { ll x, y; };
bool compX(const pos& l, const pos& r) { return l.x == r.x ? l.y < r.y : l.x < r.x; }
bool compY(const pos& l, const pos& r) { return l.y == r.y ? l.x < r.x : l.y < r.y; }

inline ll magnitude(pos& a, pos& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
pos Ax[LEN], Ay[25][LEN], merging[LEN];

int N;
ll closest(int l = 0, int r = N - 1, int depth = 0) {
	// std::cout << "range: " << l << ' ' << r << '\n';
	// for (int i = l; i <= r; ++i) std::cout << Ay[depth][i].x << ' ' << Ay[depth][i].y << '\n';

	if (r - l == 1) return magnitude(Ay[depth][l], Ay[depth][r]);
	if (r - l == 2) return std::min({ magnitude(Ay[depth][l], Ay[depth][l + 1]), magnitude(Ay[depth][l], Ay[depth][l + 2]), magnitude(Ay[depth][l + 1], Ay[depth][l + 2]) });

	int mid = (l + r) / 2;
	int li = l, ri = mid + 1;
	pos mid_pos = Ax[mid];
	for (int i = l; i <= r; ++i) {
		if ((Ay[depth][i].x < mid_pos.x || (Ay[depth][i].x == mid_pos.x && Ay[depth][i].y <= mid_pos.y)) && li <= mid)
			Ay[depth + 1][li++] = Ay[depth][i];
		else Ay[depth + 1][ri++] = Ay[depth][i];
	}

	ll dist = std::min(closest(l, mid, depth + 1), closest(mid + 1, r, depth + 1));
	ll bound = sqrt(dist);

	// merge
	int size = 0;
	for (int i = l; i <= r; ++i) if (std::abs(Ay[depth][i].x - mid_pos.x) <= bound) merging[size++] = Ay[depth][i];
	// sweep
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size && merging[j].y - merging[i].y <= bound; ++j) {
			dist = std::min(dist, magnitude(merging[i], merging[j]));
		}
	}

	return dist;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> Ax[i].x >> Ax[i].y;
		Ay[0][i] = Ax[i];
	}
	std::sort(Ax, Ax + N, compX);
	for (int i = 0; i < N - 1; ++i) {
		if (Ax[i].x == Ax[i + 1].x && Ax[i].y == Ax[i + 1].y) {
			std::cout << 0;
			return 0;
		}
	}
	std::sort(Ay[0], Ay[0] + N, compY);

	std::cout << closest();
}