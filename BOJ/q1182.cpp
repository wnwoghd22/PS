#include <iostream>

int N, S, A[20];
int count[100'000 * 40 + 1];
void dp(int index, int current, int depth) {
	if (depth > 0) count[2'000'000 + current]++;
	for (int i = index; i < N; ++i) dp(i + 1, current + A[i], depth + 1);
}

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	dp(0, 0, 0);
	std::cout << count[2'000'000 + S];
}