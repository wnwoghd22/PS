#include <iostream>
#include <algorithm>
#include <string>

const int LEN = 200'000;

struct Pos {
	int x, i;
	bool operator<(const Pos& r) const { return x < r.x; }
} p[LEN << 1];
int N, X, R, sp, stack[LEN];
std::string ans = "YES";

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> X >> R;
		p[i << 1] = { X - R, i + 1 };
		p[i << 1 | 1] = { X + R, -i - 1 };
	}
	std::sort(p, p + N * 2);
	for (int i = 0, X = -1e9; i < N * 2; ++i) {
		if (p[i].x == X) { ans = "NO"; break; }
		X = p[i].x;
		if (p[i].i < 0) {
			if (stack[sp - 1] + p[i].i) { ans = "NO"; break; }
			else --sp;
		}
		else stack[sp++] = p[i].i;
	}
	std::cout << ans;
}