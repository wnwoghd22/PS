#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 3e5 + 1;
const ll MOD = 1e8;

int N;

int A[LEN];
ll S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);

	for (int i = 1; i <= N; ++i) S[i] = S[i - 1] + A[i - 1];

	ll ret = 0;
	for (int i = 0, j = N - 1; i < N - 1; ++i) {
		if (j < i) j = i;
		while (j > i && A[i] + A[j] >= MOD) --j;
		ret += S[N] - S[i + 1] - MOD * (N - j - 1) + (ll)A[i] * (N - i - 1);
	}

	std::cout << ret;
}