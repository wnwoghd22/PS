#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
const int MAX = 200'000;
struct Vertex { int y, y1, y2, q; };
bool CompY(const Vertex& a, const Vertex& b) { return a.y < b.y; }
std::vector<int> posY;
std::vector<Vertex> v;

int N, ux, uy, vx, vy;
ll segTree[MAX * 4];
ll lazy[MAX * 4];

void propagate(int index, int start, int end) {
	if (lazy[index]) {
		segTree[index] += lazy[index];
		if (start != end) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
}

void update_diff(int left, int right, ll diff, int index = 1, int start = 0, int end = N) {
	propagate(index, start, end);

	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		segTree[index] += diff;
		if (start != end) {
			lazy[index * 2] += diff;
			lazy[index * 2 + 1] += diff;
		}
		return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);

	segTree[index] = std::max(segTree[index * 2], segTree[index * 2 + 1]);
}

ll get_max(int left, int right, int start = 0, int end = N, int index = 1) {
	propagate(index, start, end);

	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];

	int mid = (start + end) / 2;
	return std::max(get_max(left, right, start, mid, index * 2), get_max(left, right, mid + 1, end, index * 2 + 1));
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> ux >> uy >> vx >> vy;
		posY.push_back(uy); posY.push_back(vy);
		v.push_back({ vy, vy, uy, 1 });
		v.push_back({ uy, vy, uy, 0 });
	}
	std::sort(posY.begin(), posY.end());
	posY.erase(std::unique(posY.begin(), posY.end()), posY.end());
	for (Vertex& e : v) {
		if (e.q) e.y = std::lower_bound(posY.begin(), posY.end(), e.y) - posY.begin();
		else {
			int y1 = std::lower_bound(posY.begin(), posY.end(), e.y1) - posY.begin(),
				y2 = std::lower_bound(posY.begin(), posY.end(), e.y2) - posY.begin();
			e.y = y2 + 1, e.y1 = y1, e.y2 = y2;
		}
	}
	std::sort(v.begin(), v.end(), CompY);

	ll p1 = 0, p2, max = 0;
	for (int i = 0, j = 0; i < posY.size(); ++i) {
		while (j < v.size() && v[j].y == i) {
			if (v[j].q) ++p1;
			else --p1, update_diff(v[j].y1, v[j].y2, 1);
			++j;
		}
		p2 = get_max(0, i - 1);
		max = std::max(max, p1 + p2);
	}
	std::cout << max;
}