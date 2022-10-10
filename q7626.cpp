#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

typedef long long int ll;
const int MAX = 1'000'000;
struct Vertex { int x1, x2, y, diff; };
bool CompY(Vertex& a, Vertex& b) { return a.y < b.y; }

int N;
std::vector<Vertex> v;
ll segTree[MAX * 4];
ll segWidth[MAX * 4];

std::vector<ll> rankX;
std::map <ll, ll> mapX;
ll segHeight[MAX + 1];

void update_diff(int left, int right, ll diff, int index = 1, int start = 1, int end = MAX) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		segTree[index] += diff;
	}
	else {
		int mid = (start + end) >> 1;
		update_diff(left, right, diff, index << 1, start, mid);
		update_diff(left, right, diff, (index << 1) + 1, mid + 1, end);
	}

	if (segTree[index]) {
		segWidth[index] = rankX[end] - rankX[start - 1];
	}
	else {
		if (start == end) segWidth[index] = 0;
		else segWidth[index] = segWidth[index << 1] + segWidth[(index << 1) + 1];
	}
}
ll get_width() { return segWidth[1]; }

int main() {
	ll area = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		int x1, x2, y1, y2;
		std::cin >> x1 >> x2 >> y1 >> y2;
		rankX.push_back(x1);
		rankX.push_back(x2);
		v.push_back({ x1, x2, y1, 1 });
		v.push_back({ x1, x2, y2, -1 });
	}

	std::sort(rankX.begin(), rankX.end());
	rankX.erase(std::unique(rankX.begin(), rankX.end()), rankX.end());
	for (ll i = 0; i < rankX.size(); ++i) {
		mapX[rankX[i]] = i + 1;
	}

	std::sort(v.begin(), v.end(), CompY);
	int rank = 0;
	segHeight[0] = v[0].y;
	for (int i = 1; i < N * 2; ++i) {
		if (v[i].y != v[i - 1].y) {
			++rank;
			segHeight[rank] = v[i].y;
		}
	}

	for (int i = 0, j = 0; i < rank; ++i) {
		int current_y = segHeight[i];
		ll current_height = segHeight[i + 1] - segHeight[i];
		while (v[j].y == current_y) {
			update_diff(mapX[v[j].x1] + 1, mapX[v[j].x2], v[j].diff);
			++j;
		}
		ll current_width = get_width();
		
		std::cout << current_y << ' ' << current_height << ' ' << current_width << '\n';

		area += current_height * current_width;
	}
	std::cout << area;
}