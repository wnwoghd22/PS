#include "biggest.h"
#include <vector>
#include <queue>
#include <cstring>

static std::vector<int> children[100'001];

struct Comp {
	bool operator()(int a, int b) {
		return children[a].size() > children[b].size();
	}
};

static int init(int l, int r) {
	if (l == r) return l;

	if (l + 1 == r) {
		if (compare(l, r) == l) { children[l].push_back(r); return l; }
		else { children[r].push_back(l); return r; }
	}
	int lmax = init(l, (l + r) / 2);
	int rmax = init((l + r) / 2 + 1, r);

	if (compare(lmax, rmax) == lmax) { children[lmax].push_back(rmax); return lmax; }
	else { children[rmax].push_back(lmax); return rmax; }
}

static std::vector<int> biggest(int N, int K) {
	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	// for (int i = 1; i <= N; ++i) pq.push(i);
	pq.push(init(1, N));

	while (result.size() != K) {
		while (pq.size() != 1) {
			int a = pq.top(); pq.pop();
			int b = pq.top(); pq.pop();

			if (compare(a, b) == a) {
				children[a].push_back(b);
				pq.push(a);
			}
			else {
				children[b].push_back(a);
				pq.push(b);
			}
		}
		int max = pq.top(); pq.pop();
		result.push_back(max);

		for (const int& i : children[max]) pq.push(i);
	}

	return result;
}