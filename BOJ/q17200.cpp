#include <iostream>
#include <map>

std::map<std::string, int> map;
bool f[26][26 * 25];
int N, idx;
std::string S;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, k; i < N; ++i) {
		std::cin >> k;
		for (int j = 0; j < k; ++j) {
			std::cin >> S;
			if (map.find(S) == map.end()) map[S] = idx++;
			f[i][map[S]] = 1;
		}
	}
	bool ret = 1;
	for (int i = 0; i < idx; ++i) {
		for (int j = i + 1; j < idx; ++j) {
			bool bi = 0, bj = 0, bij = 0;
			for (int k = 0; k < N; ++k) {
				bi |= f[k][i] && !f[k][j];
				bj |= !f[k][i] && f[k][j];
				bij |= f[k][i] && f[k][j];
			}
			ret &= !(bi && bj && bij);
		}
	}
	std::cout << (ret ? "yes" : "no");
}