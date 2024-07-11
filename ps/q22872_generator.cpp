#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <map>
#include <string>

std::map<int, int> visited[1 << 26];

int N;
int cnt = 0;

int get_middle(int s) {
	int cnt = 0, x = s;
	while (x) {
		cnt++;
		x -= x & -x;
	}
	// std::cout << "cnt: " << cnt << '\n';
	if (cnt == 0) return 0;
	int mid = cnt / 2;
	int cur = 0;
	for (int i = 0; i < 31; ++i) {
		if (s & 1 << i) cur++;
		// std::cout << i << '\n';
		if (cur == mid + 1) return i;
	}
}

struct State {
	int s1, s2, s3;
};

int bfs(int n) {
	std::queue<State> q;
	q.push({ (1 << N) - 1, 0, 0 });
	visited[(1 << N - 1)][0] = 0;
	cnt++;

	while (q.size()) {
		State s = q.front(); q.pop();

		if (s.s1 == 1 && s.s2 == (1 << N) - 2) { // mirror state
			// std::cout << "mirror\n";
			// std::cout << cnt << '\n';
			// std::cout << visited[1][(1 << N) - 2] << '\n';
			// return visited[0][(1 << N) - 2] * 2 + 1;
		}

		if (s.s1 == 0 && s.s2 == 0) {
			return visited[0][0];
		}

		int s1 = s.s1, s2 = s.s2, s3 = s.s3;
		int d = visited[s1][s2];

		if (s1) {
			int m1 = get_middle(s1);
			int ss1 = s1 & ~(1 << m1);
			if (get_middle(s2 | 1 << m1) == m1) {
				int ss2 = s2 | 1 << m1;
				if (visited[ss1].find(ss2) == visited[ss1].end()) {
					visited[ss1][ss2] = d + 1;
					q.push({ ss1, ss2, s3 });
					cnt++;
				}
			}
			if (get_middle(s3 | 1 << m1) == m1) {
				int ss3 = s3 | 1 << m1;
				if (visited[ss1].find(s2) == visited[ss1].end()) {
					visited[ss1][s2] = d + 1;
					q.push({ ss1, s2, ss3 });
					cnt++;
				}
			}
		}

		if (s2) {
			int m2 = get_middle(s2);
			int ss2 = s2 & ~(1 << m2);
			if (get_middle(s1 | 1 << m2) == m2) {
				int ss1 = s1 | 1 << m2;
				if (visited[ss1].find(ss2) == visited[ss1].end()) {
					visited[ss1][ss2] = d + 1;
					q.push({ ss1, ss2, s3 });
					cnt++;
				}
			}
			if (get_middle(s3 | 1 << m2) == m2) {
				int ss3 = s3 | 1 << m2;
				if (visited[s1].find(ss2) == visited[s1].end()) {
					visited[s1][ss2] = d + 1;
					q.push({ s1, ss2, ss3 });
					cnt++;
				}
			}
		}

		if (s3) {
			int m3 = get_middle(s3);
			int ss3 = s3 & ~(1 << m3);
			if (get_middle(s1 | 1 << m3) == m3) {
				int ss1 = s1 | 1 << m3;
				if (visited[ss1].find(s2) == visited[ss1].end()) {
					visited[ss1][s2] = d + 1;
					q.push({ ss1, s2, ss3 });
					cnt++;
				}
			}
			if (get_middle(s2 | 1 << m3) == m3) {
				int ss2 = s2 | 1 << m3;
				if (visited[s1].find(ss2) == visited[s1].end()) {
					visited[s1][ss2] = d + 1;
					q.push({ s1, ss2, ss3 });
					cnt++;
				}
			}
		}
	}
	return -1;
}

int u[1'000'000];
int v[1'000'000];
int len;

void trace(int n) {
	int s1 = 0, s2 = 0, s3 = (1 << N) - 1;
	len = visited[0][0];
	while (!(s1 == (1 << N) - 1 && s2 == 0 && s3 == 0)) {
		int d = visited[s1][s2];

		if (s1) {
			int m1 = get_middle(s1);
			int ss1 = s1 & ~(1 << m1);
			if (get_middle(s2 | 1 << m1) == m1) {
				int ss2 = s2 | 1 << m1;
				if (visited[ss1].find(ss2) != visited[ss1].end() && visited[ss1][ss2] == d - 1) {
					u[d] = 2; v[d] = 1;
					s1 = ss1; s2 = ss2;
					continue;
				}
			}
			if (get_middle(s3 | 1 << m1) == m1) {
				int ss3 = s3 | 1 << m1;
				if (visited[ss1].find(s2) != visited[ss1].end() && visited[ss1][s2] == d - 1) {
					u[d] = 3; v[d] = 1;
					s1 = ss1; s3 = ss3;
					continue;
				}
			}
		}

		if (s2) {
			int m2 = get_middle(s2);
			int ss2 = s2 & ~(1 << m2);
			if (get_middle(s1 | 1 << m2) == m2) {
				int ss1 = s1 | 1 << m2;
				if (visited[ss1].find(ss2) != visited[ss1].end() && visited[ss1][ss2] == d - 1) {
					u[d] = 1; v[d] = 2;
					s1 = ss1; s2 = ss2;
					continue;
				}
			}
			if (get_middle(s3 | 1 << m2) == m2) {
				int ss3 = s3 | 1 << m2;
				if (visited[s1].find(ss2) != visited[s1].end() && visited[s1][ss2] == d - 1) {
					u[d] = 3; v[d] = 2;
					s2 = ss2; s3 = ss3;
					continue;
				}
			}
		}

		if (s3) {
			int m3 = get_middle(s3);
			int ss3 = s3 & ~(1 << m3);
			if (get_middle(s1 | 1 << m3) == m3) {
				int ss1 = s1 | 1 << m3;
				if (visited[ss1].find(s2) != visited[ss1].end() && visited[ss1][s2] == d - 1) {
					u[d] = 1; v[d] = 3;
					s1 = ss1; s3 = ss3;
					continue;
				}
			}
			if (get_middle(s2 | 1 << m3) == m3) {
				int ss2 = s2 | 1 << m3;
				if (visited[s1].find(ss2) != visited[s1].end() && visited[s1][ss2] == d - 1) {
					u[d] = 2; v[d] = 3;
					s2 = ss2; s3 = ss3;
					continue;
				}
			}
		}
	}
}

int main() {
	std::cin >> N;
	std::string S = std::to_string(N) + ".out";
	std::cout << S;
	freopen(S.c_str(), "w", stdout);

	std::cout << bfs(N) << '\n';
	trace(N);

	for (int i = 1; i <= len; ++i) std::cout << u[i] << ' ' << v[i] << '\n';

	// std::cout << cnt << '\n';
}