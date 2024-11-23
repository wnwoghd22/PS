#include <iostream>

const int L = 'L' - 'A';
const int O = 'O' - 'A';
const int V = 'V' - 'A';
const int E = 'E' - 'A';
const int MOD = 100;
std::string S, T, ret;
int N, f, l, o, v, e;
int c[26], k[26];
int w() {
	l = c[L] + k[L]; o = c[O] + k[O];
	v = c[V] + k[V]; e = c[E] + k[E];
	return (l + o) % MOD * (l + v) % MOD * (l + e) % MOD * (o + v) % MOD * (o + e) % MOD * (v + e) % MOD;
}

int main() {
	std::cin >> S >> N >> ret;
	for (int i = 0; i < S.length(); ++i) c[S[i] - 'A']++;
	for (int i = 0; i < ret.length(); ++i) k[ret[i] - 'A']++;
	f = w();
	for (int i = 1, g; i < N; ++i) {
		std::cin >> T;
		k[L] = k[O] = k[V] = k[E] = 0;
		for (int j = 0; j < T.length(); ++j) k[T[j] - 'A']++;
		g = w();
		if (g > f) {
			f = g;
			ret = T;
		}
		else if (g == f && T < ret) ret = T;
	}
	std::cout << ret;
}