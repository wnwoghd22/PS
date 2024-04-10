#include <iostream>
#include <cstring>
#include <string>
#include <map>

typedef long long ll;
const int LEN = 2501;
const int MOD = 1e9 + 7;

int gataca(char c) { return c == 'A' ? 0 : c == 'C' ? 1 : c == 'G' ? 2 : c == 'T' ? 3 : -1; }
int amino(int d1, int d2, int d3) { return d1 << 4 | d2 << 2 | d3; }
char A[LEN];
int N, M, D[LEN];
int pre[4][LEN], ptr[4];
int prev[65];
ll dp[LEN], S[LEN];
std::string codon, acid;
std::map<std::string, int> a_map;
int aminos[64];

int main() {
	std::cin >> A;
	N = strlen(A);
	for (int i = 0, d; i < N; ++i) { // preprocessing pre pointer
		for (int j = 0; j < 4; ++j)
			pre[j][i + 1] = ptr[j];
		d = gataca(A[i]);
		D[i + 1] = d;
		ptr[d] = i + 1;
	}

	/*for (int d = 0; d < 4; ++d) {
		for (int i = 1; i <= N; ++i)
			std::cout << pre[d][i] << ' ';
		std::cout << '\n';
	}*/

	std::cin >> M;
	while (M--) {
		std::cin >> codon >> acid;
		int i = amino(gataca(codon[0]), gataca(codon[1]), gataca(codon[2]));
		if (a_map.find(acid) == a_map.end()) a_map[acid] = a_map.size() + 1;
		aminos[i] = a_map[acid];
	}

	// for (int i = 0; i < 64; ++i) std::cout << aminos[i] << ' ';

	dp[0] = S[0] = 1;
	for (int i3 = 1, d3; i3 <= N; ++i3) {
		d3 = D[i3];
		for (int d2 = 0, i2; d2 < 4; ++d2) {
			i2 = pre[d2][i3];
			if (!i2) continue;
			for (int d1 = 0, i1; d1 < 4; ++d1) {
				i1 = pre[d1][i2];
				if (!i1) continue;

				int i = aminos[amino(d1, d2, d3)];
				if (!i) continue;
				if (i1 <= prev[i]) continue;
				if (prev[i]) dp[i3] += S[i1 - 1] - S[prev[i] - 1] + MOD;
				else dp[i3] += S[i1 - 1];
				dp[i3] %= MOD;
				prev[i] = i1;
			}
		}
		S[i3] = (dp[i3] + S[i3 - 1]) % MOD;
	}
	std::cout << (S[N] - 1 + MOD) % MOD;
}