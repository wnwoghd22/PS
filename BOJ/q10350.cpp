#include <iostream>
#include <cmath>

typedef long long int ll;
const int LEN = 10'000;
ll sum[LEN * 2];
ll S;
int N;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> sum[i], sum[i + N] = sum[i], S += sum[i];
	for (int i = 1; i < N * 2; ++i) sum[i] += sum[i - 1];
	// for (int i = 0; i < N * 2; ++i) std::cout << sum[i] << ' ';

	ll result = 0;
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			ll sub = sum[j + i] - sum[j];
			if (sub < 0)
				result += ceil((double)-sub / S);
		}
	}
	std::cout << result;
}