#include <iostream>

int height[200'001];
int count[200'001];

int main() {
	int N;
	std::cin >> N;

	for (int i = 0; i < N; ++i) std::cin >> height[i];
	for (int i = N - 1; i >= 0; --i) {
		if (height[i] == 0) count[i] = count[i + 1] + 1;
		else {
			if (i + 1 + height[i] >= N) count[i] = 1;
			else count[i] = count[i + 1 + height[i]] + 1;
		}
	}
	for (int i = 0; i < N; ++i) std::cout << count[i] << ' ';
}