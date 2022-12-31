#include <iostream>
#include <vector>

typedef long long int ll;
const int MAX = 100'001;

int N;
std::vector<int> graph[MAX];
ll s[MAX], e[MAX];
ll segTree[MAX * 4];
int order = 0;
void dfs(int v) {
	s[v] = ++order;
	for (const int& u : graph[v]) {
		if (!s[u]) dfs(u);
	}
	e[v] = order;
}
void update_diff(int left, int right, ll diff, int index = 1, int start = 1, int end = N) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		segTree[index] += diff; return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);
}

ll get_diff(int n, int start = 1, int end = N, int index = 1) {
	if (n > end || n < start) return 0;
	if (start == end) return segTree[index];
	int mid = (start + end) / 2;
	return segTree[index] + get_diff(n, start, mid, index * 2) + get_diff(n, mid + 1, end, index * 2 + 1);
}

int main() {
	int M, A;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		if (~A) graph[A].push_back(i);
	}
	dfs(1);

	while (M--) {
		ll q, a, b;
		std::cin >> q;
		if (q == 1) {
			std::cin >> a >> b;
			update_diff(s[a], e[a], b);
		}
		if (q == 2) {
			std::cin >> a;
			std::cout << get_diff(s[a]) << '\n';
		}
	}
}