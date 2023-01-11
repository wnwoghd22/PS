#include <iostream>
#include <vector>
#include <cstring>

typedef long long int ll;
const int MAX = 100'001;

int N, M, K;
ll segTree[MAX * 4];
ll lazy[MAX * 4];
std::vector<int> graph[MAX];
int s[MAX], e[MAX];
int order = 0;
void dfs(int v) {
	s[v] = ++order;
	for (const int& u : graph[v]) {
		if (!s[u]) dfs(u);
	}
	e[v] = order;
}
void propagate(int index, int start, int end) {
	if (~lazy[index]) {
		segTree[index] = (end - start + 1) * lazy[index];
		if (start != end) {
			lazy[index * 2] = lazy[index];
			lazy[index * 2 + 1] = lazy[index];
		}
		lazy[index] = -1;
	}
}

void update_diff(int left, int right, ll diff, int index = 1, int start = 1, int end = N) {
	propagate(index, start, end);

	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		segTree[index] = (end - start + 1) * diff;
		if (start != end) {
			lazy[index * 2] = diff;
			lazy[index * 2 + 1] = diff;
		}
		return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);

	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

ll get_diff(int left, int right, int start = 1, int end = N, int index = 1) {
	propagate(index, start, end);

	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];

	int mid = (start + end) / 2;
	return get_diff(left, right, start, mid, index * 2) + get_diff(left, right, mid + 1, end, index * 2 + 1);
}

int main() {
	int M, A;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		if (A) graph[A].push_back(i);
	}
	dfs(1);
	memset(segTree, -1, sizeof segTree);
	update_diff(1, N, 1);

	std::cin >> M;
	while (M--) {
		ll q, i;
		std::cin >> q >> i;
		if (q == 1) update_diff(s[i] + 1, e[i], 1);
		if (q == 2) update_diff(s[i] + 1, e[i], 0);
		if (q == 3) std::cout << get_diff(s[i] + 1, e[i]) << '\n';
	}
}