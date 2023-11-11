#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 2e5 + 1;
int N, C, mask, b[LEN], d[LEN];
char S[20];
std::queue<int> q;

int main() {
	std::cin >> C >> N;
	mask = (1 << C) - 1;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		for (int j = 0; j < C; ++j)
			b[i] |= (S[j] == 'G') << j;
	}
	memset(d, -1, sizeof d);
	for (int i = 0; i < N; ++i) {
		q.push(b[i]);
		d[b[i]] = 0;
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int j = 0; j < C; ++j) {
			int v = u ^ (1 << j);
			if (!~d[v]) {
				q.push(v);
				d[v] = d[u] + 1;
			}
		}
	}
	for (int i = 0; i < N; ++i) std::cout << C - d[mask ^ b[i]] << '\n';
}