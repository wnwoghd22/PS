#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 1500;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int p[LEN * LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a); b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int R, C;
int t[LEN * LEN];
char A[LEN][LEN + 1];
int idx, swan[2];
std::queue<int> q;

int main() {
	std::cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		std::cin >> A[i];
		for (int j = 0; j < C; ++j) {
			if (A[i][j] == 'X') continue;
			if (A[i][j] == 'L') swan[idx++] = i * C + j;
			t[i * C + j] = 1;
			q.push(i * C + j);
		}
	}
	memset(p, -1, sizeof p);
	int result = -1;
	while (q.size()) {
		int u = q.front(); q.pop();
		int x = u / C, y = u % C;
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			int v = nx * C + ny;
			if (!t[v]) t[v] = t[u] + 1, q.push(v);
			else if (t[v] <= t[u]) join(u, v);
		}
		if (find(swan[0]) == find(swan[1])) {
			result = t[u];
			break;
		}
	}
	std::cout << result - 1;
}