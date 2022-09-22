#include "biggest.h"
#include <vector>
#include <queue>

static std::vector<int> children[100'001];

struct Comp {
	bool operator()(int a, int b) {
		return children[a].size() > children[b].size();
	}
};

static std::vector<int> biggest(int N, int K) {
	for (std::vector<int>& v : children) v.clear();

	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	for (int i = 1; i <= N; ++i) pq.push(i);

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

		for (const int& child : children[max]) pq.push(child);
	}

	return result;
}