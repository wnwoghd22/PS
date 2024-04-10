#include <iostream>
#include <algorithm>

const int LEN = 30'000;
struct Line {
	int y, x1, x2, q;
	Line() {}
	Line(int y, int x1, int x2, int q) : y(y), x1(x1), x2(x2), q(q) {}
	bool operator<(const Line& r) { return y < r.y; }
} lines[LEN];
int N, x1, x2, y, y2, seg_tree[LEN * 4], seg_line[LEN * 4];

void update_diff(int left, int right, int diff, int start = 0, int end = LEN, int index = 1) {
	if (end < left || start > right) return;
	if (left <= start && end <= right) {
		seg_tree[index] += diff;
		if (start == end) {
			seg_line[index] = !!seg_tree[index];
			return;
		}
	}
	else {
		int mid = (start + end) / 2;
		update_diff(left, right, diff, start, mid, index * 2);
		update_diff(left, right, diff, mid + 1, end, index * 2 + 1);
	}
	seg_line[index] = std::max(!!seg_tree[index] * (end - start + 1), seg_line[index * 2] + seg_line[index * 2 + 1]);
}

int get_line() { return seg_line[1]; }

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> x1 >> y >> x2 >> y2;
		lines[i * 2] = Line(y, x1, x2, 1);
		lines[i * 2 + 1] = Line(y2, x1, x2, -1);
	}
	int result = 0;
	std::sort(lines, lines + N * 2);
	for (int i = 0, j = 0; i <= LEN; ++i) {
		while (j < N * 2 && lines[j].y == i) {
			update_diff(lines[j].x1, lines[j].x2 - 1, lines[j].q);
			++j;
		}
		result += get_line();
	}
	std::cout << result;
}