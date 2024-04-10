#include <iostream>
#include <set>

char s[10][10];
std::set<int> sq;
int N, M;
int ans = -1;

void check(int i, int j, int dx, int dy) {
	int arr[10];
	int idx = 0;
	while (i >= 0 && i < N && j >= 0 && j < M) {
		arr[idx++] = s[i][j] - '0';
		i += dx;
		j += dy;
	}
	int num = 0;
	for (int d = 0; d < idx; ++d) {
		num = num * 10 + arr[d];
		if (sq.find(num) != sq.end()) ans = std::max(ans, num);
	}
	num = 0;
	for (int d = 0, e = 1; d < idx; ++d, e *= 10) {
		num = num + arr[d] * e;
		if (sq.find(num) != sq.end()) ans = std::max(ans, num);
	}
}

int main() {
	for (int i = 0; i <= 31623; ++i) sq.insert(i * i);

	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> s[i];

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int dy = 0; dy <= M; ++dy) {
				for (int dx = -N; dx <= N; ++dx) {
					if (dx || dy)
						check(i, j, dx, dy);
				}
			}
		}
	}
	std::cout << ans;
}