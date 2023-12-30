#include "biggest.h"
#include <vector>
#include <queue>

static std::vector<int> children[100'001];
static int height[100'001];
static int _size[100'001];

struct Comp {
	bool operator()(int a, int b) {
		return children[a].size() > children[b].size();
	}
};

static void merge(int a, int b) {
	children[a].push_back(b);
}

static int merge_two(int a, int b) {
	int d = compare(a, b);
	if (d == a) merge(a, b);
	else merge(b, a);
	return d;
}

static int merge_three(int a, int b, int c) {
	int d = compare(a, b);
	if (d == a) merge(a, b);
	else merge(b, a);
	int e = compare(c, d);
	if (e == c) merge(c, d);
	else merge(d, c);
	return e;
}

static std::vector<int> biggest(int N, int K) {
	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	for (int i = 1; i <= N - 2; i += 3)
		pq.push(merge_three(i, i + 1, i + 2));
	if (N % 3 == 1) pq.push(N);
	if (N % 3 == 2) pq.push(merge_two(N, N - 1));

	while (result.size() != K) {
		while (pq.size() != 1) {
			int a = pq.top(); pq.pop();
			int b = pq.top(); pq.pop();
			pq.push(merge_two(a, b));
		}
		int max = pq.top(); pq.pop();
		result.push_back(max);

		for (const int& i : children[max]) pq.push(i);
	}

	return result;
}