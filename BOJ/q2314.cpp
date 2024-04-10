#include <iostream>
#include <queue>
#include <cstring>

char c;
int start, end, visited[1 << 16];
std::queue<int> q;

int main() {
	start = end = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cin >> c;
			start |= (c == 'L') << (i << 2 | j);
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cin >> c;
			end |= (c == 'L') << (i << 2 | j);
		}
	}
	memset(visited, -1, sizeof visited);
	visited[start] = 0;
	q.push(start);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (u == end) break;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 3; ++j) {
				if ((u & 1 << (i << 2 | j)) ^ (u & 2 << (i << 2 | j))) {
					int v = u ^ (3 << (i << 2 | j));
					if (~visited[v]) continue;
					visited[v] = visited[u] + 1;
					q.push(v);
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 4; ++j) {
				if ((u & 1 << (i << 2 | j)) ^ (u & 16 << (i << 2 | j))) {
					int v = u ^ (17 << (i << 2 | j));
					if (~visited[v]) continue;
					visited[v] = visited[u] + 1;
					q.push(v);
				}
			}
		}
	}
	std::cout << visited[end];
}