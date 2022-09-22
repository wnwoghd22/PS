#include "biggest.h"
#include <vector>
#include <queue>
#include <cstring>

// static std::vector<int> children[100'001];
static int children[100'001][20];
static int _size[100'001];

struct Comp {
	bool operator()(int a, int b) {
		return _size[a] > _size[b];
	}
};

static std::vector<int> biggest(int N, int K) {
	memset(children, 0, sizeof children);
	memset(_size, 0, sizeof _size);

	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	for (int i = 1; i <= N; ++i) pq.push(i);

	while (result.size() != K) {
		while (pq.size() != 1) {
			int a = pq.top(); pq.pop();
			int b = pq.top(); pq.pop();

			if (compare(a, b) == a) {
				children[a][_size[a]++] = b;
				pq.push(a);
			}
			else {
				children[b][_size[b]++] = a;
				pq.push(b);
			}
		}
		int max = pq.top(); pq.pop();
		result.push_back(max);

		for (int i = 0; i < _size[max]; ++i) pq.push(children[max][i]);
	}

	return result;
}