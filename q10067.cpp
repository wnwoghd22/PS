#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 100'001;
ll dp[201][LEN], S[LEN];
inline ll fa(int k, int x) { return dp[k][x]; }
inline ll fb(int k, int x) { return -S[x] * dp[k][x]; }

int N, K, a, hull[201][LEN], _size[201], ptr[201];
ld xpos[201][LEN];
ld intersect(int k, int r, int l) {
	ld a1 = fa(k, r), b1 = fb(k, r);
	ld a2 = fa(k, l), b2 = fb(k, l);
	return (b1 - b2) / (a2 - a1);
}
std::vector<std::pair<int, int>> _stack;
void add_line(int k, int n) {
	if (!_size) {
		hull[k][++_size[k]] = n;
		xpos[k][_size[k]] = -INF;
		return;
	}
	while (_size[k] > 1 && xpos[k][_size[k]] > intersect(k, hull[k][_size[k]], n)) --_size[k];
	hull[k][++_size[k]] = n;
	xpos[k][_size[k]] = intersect(k, hull[k][_size[k] - 1], n);
	if (ptr[k] > _size[k]) ptr[k] = _size[k];
}
int binary_search(int k, int x) {
	int l = 1, r = _size[k];
	int result = 0, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (xpos[k][mid] <= S[x]) {
			result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return result;
}
ll f(int k, ll x) {
	int ptr = binary_search(k - 1, x);
	return fa(k - 1, hull[k - 1][ptr]) * S[x] + fb(k - 1, hull[k - 1][ptr]);
}

// TODO: need to fix
int main() {
	std::cin >> N >> K;
	for (ll i = 1, p = 1; i <= N; ++i) {
		std::cin >> a;
		dp[0][i] = S[i] = S[i - 1] + a;
		if (i <= K + 1) {
			p *= a;
			dp[i - 1][i] = p;
			add_line(i - 1, i);
		}
	}
	for (int n = 3; n <= N; ++n) {
		add_line(0, n - 1);
		for (int k = 1; k <= std::min(n - 2, K); ++k) {
			dp[k][n] = f(k, n);
			_stack.push_back({ k, n });
		}
		while (_stack.size()) add_line(_stack.back().first, _stack.back().second), _stack.pop_back();
	}

	std::cout << dp[K][N];
}