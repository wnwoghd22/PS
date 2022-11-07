#include <iostream>

typedef long long int ll;
int N, S, A1[20], A2[20];
ll count1[100'000 * 40 + 1], count2[100'000 * 40 + 1];
void dp1(int index, int current, int depth) {
	if (depth > 0) count1[2'000'000 + current]++;
	for (int i = index; i < N >> 1; ++i) dp1(i + 1, current + A1[i], depth + 1);
}
void dp2(int index, int current, int depth) {
	if (depth > 0) count2[2'000'000 + current]++;
	for (int i = index; i < N - (N >> 1); ++i) dp2(i + 1, current + A2[i], depth + 1);
}

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < N >> 1; ++i) std::cin >> A1[i];
	for (int i = 0; i < N - (N >> 1); ++i) std::cin >> A2[i];
	dp1(0, 0, 0), dp2(0, 0, 0);

	ll result = 0;
	for (int i = 0, o = 4'000'000 + S; i <= 4'000'000 && o >= 0; ++i, --o) {
		if (o > 4'000'000) continue;
		result += count1[i] * count2[o];
		if (o == 2'000'000) result += count1[i];
		if (i == 2'000'000) result += count2[o];
	}

	std::cout << result;
}