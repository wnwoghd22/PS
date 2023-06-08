#include <iostream>

typedef long long ll;
const int LEN = 1501;

int N, A;
ll sum[LEN][LEN];

struct Fenwick {
private:
	ll t[LEN];
	void update(int i, ll d) {
		while (i <= N) {
			t[i] += d;
			i += i & -i;
		}
	}
public:
	ll operator[](int i) {
		ll result = 0;
		while (i > 0) {
			result += t[i];
			i -= i & -i;
		}
		return result;
	}
	void update(int l, int r, ll d) {
		update(l, d);
		update(r + 1, -d);
	}
} dp[LEN];

char q;
ll result;

int increase(int row, int col) {
	int l = col, r = col;
	int diff = 0;
	while (r < N && dp[row][r] + 1 > dp[row - 1][r + 1]) ++r;
	dp[row].update(l, r, 1);
	diff += r - l + 1;

	for (int i = row + 1; l <= r && i <= N; ++i) {
		while (l <= r && dp[i][l - 1] >= dp[i - 1][l]) ++l;
		if (l > r) break;
		while (r < N && dp[i][r] + 1 > dp[i - 1][r + 1]) ++r;
		dp[i].update(l, r, 1);
		diff += r - l + 1;
	}
	return diff;
}
int decrease(int row, int col) {
	int l = col, r = col;
	int diff = 0;
	while (r < N && dp[row][r] - 1 >= dp[row - 1][r + 1]) ++r;
	dp[row].update(l, r, -1);
	diff += r - l + 1;

	for (int i = row + 1; l <= r && i <= N; ++i) {
		while (l <= r && dp[i][l - 1] > dp[i - 1][l]) ++l;
		if (l > r) break;
		while (r < N && dp[i][r] + 1 >= dp[i - 1][r + 1]) ++r;
		dp[i].update(l, r, -1);
		diff += r - l + 1;
	}
	return diff;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			std::cin >> A;
			sum[i][j] = std::max(sum[i][j - 1], sum[i - 1][j]) + A;
			dp[i].update(j, j, sum[i][j]);
			result += sum[i][j];
		}
	}
	std::cout << result << '\n';

	for (int i = 1, r, c; i <= N; ++i) {
		std::cin >> q >> r >> c;
		if (q == 'U') result += increase(r, c);
		if (q == 'D') result -= decrease(r, c);
		std::cout << result << '\n';
	}
}