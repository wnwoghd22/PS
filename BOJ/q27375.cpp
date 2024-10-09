#include <iostream>

typedef long long int ll;
bool schedule[5][11];
int lecture[20][3];
int N, K;

ll dfs(int i, int d) {
	if (i == N) {
		return d == K;
	}
	ll result = 0;
	int day = lecture[i][0], s = lecture[i][1], e = lecture[i][2];
	if (day != 5) {
		bool flag = true;
		for (int t = s; t <= e; ++t) {
			if (schedule[day][t]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			for (int t = s; t <= e; ++t) {
				schedule[day][t] = true;
			}
			result += dfs(i + 1, d + e - s + 1);
			for (int t = s; t <= e; ++t) {
				schedule[day][t] = false;
			}
		}
	}
	result += dfs(i + 1, d);

	return result;
}

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> lecture[i][0] >> lecture[i][1] >> lecture[i][2];
	}
	std::cout << dfs(0, 0);
}