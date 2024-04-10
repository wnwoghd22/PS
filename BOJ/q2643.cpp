#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
bool compare(const pii& a, const pii& b) {
	return (a.first <= b.first && a.second <= b.second
		|| a.first <= b.second && a.second <= b.first);
}
std::vector<int> graph[101];
pii paper[101];
int N, visited[101], incoming[101];

int topological_sort() {
	int max_count = 1;
	std::queue<int> Q;
	for (int i = 1; i <= N; ++i) {
		if (!incoming[i]) {
			visited[i] = 1;
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (const int& v : graph[u]) {
			if (!--incoming[v]) {
				visited[v] = visited[u] + 1;
				max_count = std::max(visited[v], max_count);
				Q.push(v);
			}
		}
	}
	return max_count;
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> paper[i].first >> paper[i].second;
	for (int i = 1; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (compare(paper[i], paper[j])) graph[i].push_back(j), incoming[j]++;
			if (compare(paper[j], paper[i])) graph[j].push_back(i), incoming[i]++;
		}
	}
	std::cout << topological_sort();
}