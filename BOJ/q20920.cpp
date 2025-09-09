#include <iostream>
#include <algorithm>
#include <string>
#include <map>

const int LEN = 100'001;

struct E {
	std::string s;
	int cnt;
	bool operator<(const E& o) const {
		if (cnt != o.cnt) return cnt > o.cnt;
		if (s.length() != o.s.length()) return s.length() > o.s.length();
		return s < o.s;
	}
} e[LEN];

std::map<std::string, int> map;
std::string S;
int N, M, L;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		if (S.length() < M) continue;
		if (map.find(S) == map.end()) {
			map[S] = L;
			e[L].s = S;
			L++;
		}
		e[map[S]].cnt++;
	}
	std::sort(e, e + L);
	for (int i = 0; i < L; ++i) std::cout << e[i].s << '\n';
}