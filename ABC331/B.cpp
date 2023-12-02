#include <iostream>
#include <algorithm>

int N, S, M, L, cost[101];

int main() {
	std::cin >> N >> S >> M >> L;
	for (int i = 1; i <= 100; ++i) cost[i] = S * ((i - 1) / 6 + 1);
	
	for (int i = 1; i <= 100; ++i) {
		cost[i] = std::min(cost[i], M * ((i - 1) / 8 + 1));
		for (int j = i - 8, k = 1; j >= 0; j -= 8, ++k) {
			cost[i] = std::min(cost[i], M * k + cost[j]);
		}
	}

	for (int i = 1; i <= 100; ++i) {
		cost[i] = std::min(cost[i], L * ((i - 1) / 12 + 1));
		for (int j = i - 12, k = 1; j >= 0; j -= 12, ++k) {
			cost[i] = std::min(cost[i], L * k + cost[j]);
		}
	}

	std::cout <<  cost[N];
}