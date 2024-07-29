#include <iostream>

typedef long long ll;
const ll MOD = 1e17;
char S[110];
ll x[10];

int main() {
	std::cin >> S;
	for (ll i = strlen(S) - 1, j = 1, k = 0; ~i; --i) {
		x[k] += (S[i] - '0') * j;
		if ((j *= 10) == MOD) ++k, j = 1;
	}
	int ret = 1;
	if (~x[0] & 1) ret += 2, x[0]--;
	bool f = 1;
	while (f) {
		f = (x[0] >>= 1);
		for (int i = 1; i < 10; ++i) {
			if (x[i] & 1) x[i - 1] += MOD / 2;
			f |= (x[i] >>= 1);
		}
		ret += 2;
	}
	std::cout << ret;
}