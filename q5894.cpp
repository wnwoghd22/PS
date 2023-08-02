#include <iostream>

typedef long long ll;

int N;
int px[11], py[11];
int x[11], y[11];

int dir(int i, int j) {
	int dx = x[j] - x[i];
	int dy = y[j] - y[i];
	if (!dx && !dy) return -1;
	if (dx && dy) return -1;
	if (!dx && dy > 0) return 0;
	if (!dx && dy < 0) return 1;
	if (dx > 0 && !dy) return 2;
	if (dx < 0 && !dy) return 3;
}

int seq[11];

ll dfs(int i, int b) {
	if (i == N + 1) return ~dir(N - 1, N) && ~dir(N, 0) && dir(N - 1, N) ^ dir(N, 0);
	
	ll ret = 0;
	for (int j = 1; j <= N; ++j) {
		if (b & 1 << j) continue;
		x[i] = px[j];
		y[i] = py[j];
		if ((i == 1 && ~dir(0, 1)) || ~dir(i - 1, i) && dir(i - 2, i - 1) ^ dir(i - 1, i)) ret += dfs(i + 1, b | 1 << j);
	}
	return ret;
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> px[i] >> py[i];
	std::cout << dfs(1, 0);
}