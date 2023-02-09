#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>

const int LEN = 100'000;
struct Line {
	int l, r;
	bool operator<(const Line& rhs) const { return r < rhs.r; }
} lines[LEN];

int N, d;

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N;
	for (int i = 0, tmp; i < N; ++i) {
		std::cin >> lines[i].l >> lines[i].r;
		if (lines[i].l > lines[i].r) {
			tmp = lines[i].l; lines[i].l = lines[i].r; lines[i].r = tmp;
		}
	}
	std::sort(lines, lines + N);

	std::cin >> d;
	std::priority_queue<int> q;
	int result = 0;
	for (int i = 0; i < N; ++i) {
		if (lines[i].r - lines[i].l > d) continue;
		while (q.size() && lines[i].r + q.top() > d) q.pop();
		q.push(-lines[i].l);
		if (q.size() > result) result = q.size();
	}
	std::cout << result;
}