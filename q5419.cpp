#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long int ll;
typedef std::pair<std::pair<int, int>, int> pos;
const int MAX = 75'000;
int segTree[MAX * 4];
int N;

void push(int n, int index = 1, int start = 1, int end = MAX) {
	if (n > end || n < start) return;
	if (start <= n && n <= end) ++segTree[index];
	if (start == end) return;

	int mid = (start + end) / 2;
	push(n, index * 2, start, mid);
	push(n, index * 2 + 1, mid + 1, end);
}
int get_sum(int left, int right, int index = 1, int start = 1, int end = MAX) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];
	int mid = (start + end) / 2;
	return get_sum(left, right, index * 2, start, mid) + get_sum(left, right, index * 2 + 1, mid + 1, end);

}

bool CompX(pos& a, pos& b) { 
	return a.first.first < b.first.first ? true : 
		(a.first.first == b.first.first) && a.first.second > b.first.second;
}
bool CompY(pos& a, pos& b) { return a.first.second < b.first.second; }

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll count = 0;
		std::cin >> N;
		memset(segTree, 0, sizeof segTree);

		std::vector<std::pair<std::pair<int, int>, int>> v;
		for (int x, y, i = 0; i < N; ++i) {
			std::cin >> x >> y;
			v.push_back({ {x, y}, 0 });
		}

		std::sort(v.begin(), v.end(), CompY);

		int rank = 1;
		v[0].second = rank;
		for (int i = 1; i < N; ++i) {
			if (v[i].first.second != v[i - 1].first.second) ++rank;
			v[i].second = rank;
		}
		for (const pos& p : v) {
			std::cout << p.first.first << ' ' << p.first.second << ' ' << p.second << '\n';
		}

		std::sort(v.begin(), v.end(), CompX);
		for (const pos& p : v) {
			count += get_sum(p.second, rank);
			push(p.second);
		}
		std::cout << count << '\n';
	}
}