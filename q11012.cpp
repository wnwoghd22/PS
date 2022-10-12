#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int MAX = 100'000;
struct Vertex { int x1, x2, y, diff; };
bool CompY(Vertex& a, Vertex& b) { return a.y < b.y; }
struct Pos { int x, y; };
bool CompPosY(Pos& a, Pos& b) { return a.y < b.y; }

int N, M;
std::vector<Vertex> v;
std::vector<Pos> p;
ll seg_range[MAX * 4]; // 퍼레이드 선분의 누적 범위 조회
ll seg_pos[MAX * 4]; // 달걀을 던지는 사람들의 수 조회
ll seg_count[MAX * 4]; // (선분 누적 범위) * (범위 내 사람들의 수)

void update_range(int left, int right, ll diff, int index = 1, int start = 0, int end = MAX) {
	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		seg_range[index] += diff;
	}
	else {
		int mid = (start + end) >> 1;
		update_range(left, right, diff, index << 1, start, mid);
		update_range(left, right, diff, (index << 1) + 1, mid + 1, end);
	}
	seg_count[index] = seg_count[index << 1] + seg_count[(index << 1) + 1] + seg_pos[index] * seg_range[index];
}
void update_pos(int pos, ll diff, int index = 1, int start = 0, int end = MAX) {
	if (pos > end || pos < start) return;
	
	seg_pos[index] += diff;

	if (start == end) {
		seg_count[index] = seg_pos[index] * seg_range[index];
		return;
	}

	int mid = (start + end) >> 1;
	update_pos(pos, diff, index << 1, start, mid);
	update_pos(pos, diff, (index << 1) + 1, mid + 1, end);

	seg_count[index] = seg_count[index << 1] + seg_count[(index << 1) + 1] + seg_pos[index] * seg_range[index];
}
ll get_count() { return seg_count[1]; }

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(seg_range, 0, sizeof seg_range);
		memset(seg_count, 0, sizeof seg_count);
		memset(seg_pos, 0, sizeof seg_pos);
		v.clear();
		p.clear();

		ll total = 0;
		std::cin >> N >> M;
		for (int i = 0; i < N; ++i) {
			int x, y;
			std::cin >> x >> y;
			p.push_back({ x, y });
		}
		for (int i = 0; i < M; ++i) {
			int x1, x2, y1, y2;
			std::cin >> x1 >> x2 >> y1 >> y2;
			v.push_back({ x1, x2, y1, 1 });
			v.push_back({ x1, x2, y2 + 1, -1 });
		}

		std::sort(p.begin(), p.end(), CompPosY);
		std::sort(v.begin(), v.end(), CompY);

		std::vector<int> stack;
		for (int y = 0, i = 0, j = 0; y <= MAX; ++y) {
			while (!stack.empty()) update_pos(stack.back(), -1), stack.pop_back();
			while (i < v.size() && v[i].y == y) {
				update_range(v[i].x1, v[i].x2, v[i].diff);
				i++;
			}
			while (j < p.size() && p[j].y == y) {
				update_pos(p[j].x, 1);
				stack.push_back(p[j].x);
				j++;
			}
			total += get_count();

			if (i == v.size() && j == p.size()) break;
		}
		std::cout << total << '\n';
	}
}