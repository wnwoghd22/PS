#include <iostream>
#include <vector>

#define r first
#define c second

std::vector<std::pair<int, int>> queen;
int dx[8] = { -1, -1, -1,  0,  0,  1, 1, 1 };
int dy[8] = { -1,  0,  1, -1,  1, -1, 0, 1 };
bool check;
bool stale[8];
int N, K, R, C;

int main() {
	std::cin >> N >> K;
	std::cin >> R >> C;
	int ri, ci;
	while (K--) {
		std::cin >> ri >> ci;
		queen.push_back({ ri, ci });
	}
	for (const auto& q : queen) {
		if (q.r == R || q.c == C || q.r - R == q.c - C || q.r - R == C - q.c) {
			check = true;
			break;
		}
	}
	for (int i = 0; i < 8; ++i) {
		int dr = R + dx[i], dc = C + dy[i];
		if (dr <= 0 || dr > N || dc <= 0 || dc > N) {
			stale[i] = true;
			continue;
		}
		for (const auto& q : queen) {
			if (q.r == dr || q.c == dc || q.r - dr == q.c - dc || q.r - dr == dc - q.c) {
				stale[i] = true;
				break;
			}
		}
	}
	bool stalemate = true;
	for (int i = 0; i < 8; ++i) if (!stale[i]) stalemate = false;

	if (check && stalemate) std::cout << "CHECKMATE";
	else if (check) std::cout << "CHECK";
	else if (stalemate) std::cout << "STALEMATE";
	else std::cout << "NONE";
}