#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int L_MAX = 8'001;
const int G_MAX = 800;
ll dp[G_MAX][L_MAX], C, S[L_MAX];
int L, G;

ll c(int g, ll i, ll j) { return dp[g - 1][i - 1] + (j - i + 1) * (S[j] - S[i - 1]); }
void f(int g, int s, int e, int l, int r) {
	if (s > e) return;
	int m = s + e >> 1;
	int opt = l;
	for (int i = opt; i <= std::min(m, r); ++i)
		if (c(g, i, m) < c(g, opt, m)) opt = i;
	dp[g][m] = c(g, opt, m);

	f(g, s, m - 1, l, opt);
	f(g, m + 1, e, opt, r);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> L >> G;
	for (int i = 1; i <= L; ++i) {
		std::cin >> C;
		S[i] = S[i - 1] + C;
	}

	// init
	for (int i = 1; i <= L; ++i) dp[0][i] = S[i] * i;
	
	for (int i = 1; i < G; ++i) f(i, i + 1, L, i + 1, L);

	for (int i = 0; i < G; ++i) {
		for (int j = 1; j <= L; ++j)
			std::cout << dp[i][j] << ' ';
		std::cout << '\n';
	}

	std::cout << dp[G - 1][L];
}