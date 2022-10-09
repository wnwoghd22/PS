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
std::map<int, int> rankX;
ll segWidth[MAX + 1];
ll segHeight[MAX + 1];

void update_diff(int left, int right, ll diff, int index = 1, int start = 1, int end = MAX) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		segTree[index] += diff; return;
	}
	int mid = (start + end) >> 1;
	update_diff(left, right, diff, index << 1, start, mid);
	update_diff(left, right, diff, (index << 1) + 1, mid + 1, end);
}
ll get_width(int index = 1, int start = 1, int end = MAX) {
	if (segTree[index]) return segWidth[end + 1] - segWidth[start];
	if (start == end) return 0;

	int mid = (start + end) >> 1;
	return get_width(index << 1, start, mid) + get_width((index << 1) + 1, mid + 1, end);
}

int main() {
	ll area = 0;
	std::cin >> N;
	std::vector<int> posX;
	for (int i = 0; i < N; ++i) {
		int x1, x2, y1, y2;
		std::cin >> x1 >> x2 >> y1 >> y2;
		posX.push_back(x1);
		posX.push_back(x2);
		v.push_back({ x1, x2, y1, 1 });
		v.push_back({ x1, x2, y2, -1 });
	}

	std::sort(posX.begin(), posX.end());
	int rank = 1;
	rankX[posX[0]] = 1;
	segWidth[1] = posX[0];
	for (int i = 1; i < N * 2; ++i) {
		if (posX[i] != posX[i - 1]) {
			++rank;
			rankX[posX[i]] = rank;
			segWidth[rank] = posX[i];
		}
	}
	for (const auto& [k, v] : rankX) {
		std::cout << k << ' ' << v << '\n';
	}
	std::cout << "width: ";
	for (int i = 1; i <= rank; ++i)
		std::cout << segWidth[i] << ' ';
	std::cout << '\n';

	std::sort(v.begin(), v.end(), CompY);
	rank = 0;
	segHeight[0] = v[0].y;
	for (int i = 1; i < N * 2; ++i) {
		if (v[i].y != v[i - 1].y) {
			++rank;
			segHeight[rank] = v[i].y;
		}
	}
	std::cout << "height: ";
	for (int i = 0; i <= rank; ++i)
		std::cout << segHeight[i] << ' ';
	std::cout << '\n';

	for (int i = 0, j = 0; i < rank; ++i) {
		int current_y = segHeight[i];
		ll current_height = segHeight[i + 1] - segHeight[i];
		while (v[j].y == current_y) {
			update_diff(rankX[v[j].x1], rankX[v[j].x2] - 1, v[j].diff);
			++j;
		}
		ll current_width = get_width();
		
		std::cout << current_y << ' ' << current_height << ' ' << current_width << '\n';

		area += current_height * current_width;
	}
	std::cout << area;
}