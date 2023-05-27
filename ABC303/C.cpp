#include <iostream>
#include <set>

const int LEN = 4e5 + 1;
int N, M, H, K, x, y;
char S[LEN];

std::set<int> items[LEN];

int main() {
	std::cin >> N >> M >> H >> K >> S;
	for (int i = 0; i < M; ++i) {
		std::cin >> x >> y;
		items[20000 + x].insert(y);
	}
	x = 20000, y = 0;
	bool flag = true;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'R') ++x;
		else if (S[i] == 'L') --x;
		else if (S[i] == 'U') ++y;
		else if (S[i] == 'D') --y;
		--H;

		if (H < 0) {
			flag = false;
			break;
		}

		if (H < K) {
			if (items[x].find(y) != items[x].end()) {
				H = K;
				items[x].erase(y);
			}
		}
	}
	std::cout << (flag ? "Yes" : "No");
}