#include <iostream>
#include <vector>

typedef long long int ll;
const int MAX = 100'001;

int N;
std::vector<int> graph[MAX];
ll s[MAX], e[MAX];
ll segTree[MAX * 4];
int order = 1;
void dfs(int v) {
	s[v] = order++;
	for (const int& u : graph[v]) {
		if (!s[u]) dfs(u);
	}
	e[v] = order;
}
void update_diff(int n, ll diff, int index = 1, int start = 1, int end = N) {
	if (n > end || n < start) return;
	segTree[index] += diff;
	
	if (start == end) return;
	int mid = (start + end) / 2;
	update_diff(n, diff, index * 2, start, mid);
	update_diff(n, diff, index * 2 + 1, mid + 1, end);
}

ll get_sum(int left, int right, int index = 1, int start = 1, int end = N) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];
	int mid = (start + end) / 2;
	return get_sum(left, right, index * 2, start, mid) + get_sum(left, right, index * 2 + 1, mid + 1, end);
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
		ll q, a, b, c;
		std::cin >> q;
		if (q == 1) {
			std::cin >> a >> c;
			a = s[a];
			update_diff(a, c);
		}
		if (q == 2) {
			std::cin >> a;
			std::cout << get_sum(s[a], N) << '\n';
		}
	}
}