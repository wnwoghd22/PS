#include <iostream>

typedef long long ll;
const int LEN = 250'001;

int N;
char S[LEN];

int main() {
	std::cin >> N >> S;
	ll cnt = 0;
	for (ll i = 0, j = 0; i < N; ++i) {
		if (S[i] == '<') j = 0;
		if (S[i] == '>') cnt += ++j;
	}
	std::cout << cnt;
}