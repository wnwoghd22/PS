#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long int ll;
struct Pos { int idx, x, y, rank; };
const ll MOD = 1'000'000'007;
const int MAX = 200'000;
int segTree[MAX * 4];
int N;
ll left[MAX];
ll right[MAX];

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

bool CompX(Pos& a, Pos& b) { return a.x < b.x ? true : (a.y == b.y) && a.y < b.y; }
bool CompX_r(Pos& a, Pos& b) { return a.x < b.x ? true : (a.x == b.x) && a.y > b.y; }
bool CompY(Pos& a, Pos& b) { return a.y < b.y; }

int main() {
	ll count = 0;
	std::cin >> N;

	std::vector<Pos> v;
	for (int x, y, i = 0; i < N; ++i) {
		std::cin >> x >> y;
		v.push_back({ i, x, y, 0 });
	}

	std::sort(v.begin(), v.end(), CompY);

	int rank = 1;
	v[0].rank = rank;
	for (int i = 1; i < N; ++i) {
		if (v[i].y != v[i - 1].y) ++rank;
		v[i].rank = rank;
	}
	std::cout << "sorted Y:\n";
	for (const Pos& p : v) {
		std::cout << p.x << ' ' << p.y << ' ' << p.rank << '\n';
	}

	std::sort(v.begin(), v.end(), CompX);
	std::cout << "sorted X:\n";
	for (const Pos& p : v) {
		std::cout << p.x << ' ' << p.y << ' ' << p.rank << '\n';
	}

	for (int i = 0; i < N; ++i) {
		left[v[i].idx] = get_sum(v[i].rank + 1, rank);
		push(v[i].rank);
	}

	memset(segTree, 0, sizeof segTree);

	std::sort(v.begin(), v.end(), CompX_r);
	std::cout << "sorted X_r:\n";
	for (const Pos& p : v) {
		std::cout << p.x << ' ' << p.y << ' ' << p.rank << '\n';
	}

	for (int i = N - 1; i >= 0; --i) {
		right[v[i].idx] = get_sum(v[i].rank + 1, rank);
		push(v[i].rank);
	}

	std::cout << "calc:\n";
	for (int i = 0; i < N; ++i) {
		std::cout << left[i] << ' ' << right[i] << '\n';
		count += left[i] * right[i];
		count %= MOD;
	}
	std::cout << count;
}