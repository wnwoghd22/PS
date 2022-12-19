#include "biggest.h"
#include <vector>
#include <queue>

static std::vector<int> children[100'001];
static int height[100'001];
static int _size[100'001];

struct Comp {
	bool operator()(int a, int b) {
		if (children[a].size() == children[b].size()) {
			if (height[a] == height[b]) return _size[a] < _size[b];
			return height[a] > height[b];
		}
		return children[a].size() > children[b].size();
	}
};

static void merge(int a, int b) {
	height[a] = std::max(height[a], height[b] + 1);
	_size[a] += _size[b];
	children[a].push_back(b);
}

static int init(int l, int r) {
	if (l == r) return l;

	if (l + 1 == r) {
		if (compare(l, r) == l) { 
			merge(l, r); return l; 
		}
		else {
			merge(r, l); return r;
		}
	}
	int lmax = init(l, (l + r) / 2);
	int rmax = init((l + r) / 2 + 1, r);

	if (compare(lmax, rmax) == lmax) {
		merge(lmax, rmax); return lmax;
	}
	else { 
		merge(rmax, lmax); return rmax;
	}
}

static std::vector<int> biggest(int N, int K) {
	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	// for (int i = 1; i <= N; ++i) pq.push(i);
	for (int i = 1; i <= N; ++i) _size[i] = 1;
	pq.push(init(1, N));

	while (result.size() != K) {
		while (pq.size() != 1) {
			int a = pq.top(); pq.pop();
			int b = pq.top(); pq.pop();

			if (compare(a, b) == a) {
				merge(a, b);
				pq.push(a);
			}
			else {
				merge(b, a);
				pq.push(b);
			}
		}
		int max = pq.top(); pq.pop();
		result.push_back(max);

		for (const int& i : children[max]) pq.push(i);
	}

	return result;
}