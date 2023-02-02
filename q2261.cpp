#include <iostream>
#include <algorithm>

typedef long long int ll;
const int LEN = 100'000;
const int INF = 1e17;
struct pos { ll x, y; };
bool compX(const pos& l, const pos& r) { return l.x == r.x ? l.y < r.y : l.x < r.x; }
bool compY(const pos& l, const pos& r) { return l.y == r.y ? l.x < r.x : l.y < r.y; }

inline ll magnitude(pos& a, pos& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
pos Ax[LEN], Ay[LEN], merging[LEN];

int N;
ll closest(int l = 0, int r = N - 1) {
	if (r - l == 1) return magnitude(Ax[l], Ax[r]);
	if (r - l == 2) return std::min({ magnitude(Ax[l], Ax[l + 1]), magnitude(Ax[l], Ax[l + 2]), magnitude(Ax[l + 1], Ax[l + 2]) });

	int mid = (l + r) / 2;
	ll dist = std::min(closest(l, mid), closest(mid + 1, r));
	ll bound = sqrt(dist);

	// merge
	ll mid_x = Ax[mid].x;
	int size = 0;
	for (int i = 0; i < N; ++i) if (std::abs(Ay[i].x - mid_x) <= bound) merging[size++] = Ay[i];
	// sweep
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size && merging[j].y - merging[i].y < bound; ++j) {
			dist = std::min(dist, magnitude(merging[i], merging[j]));
		}
	}

	return dist;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> Ax[i].x >> Ax[i].y;
		Ay[i] = Ax[i];
	}
	std::sort(Ax, Ax + N, compX);
	std::sort(Ay, Ay + N, compY);

	std::cout << closest();
}