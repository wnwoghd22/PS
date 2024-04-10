#include <algorithm>
#include <iostream>

int num[1000];

int main() {
	int N, L;
	std::cin >> N >> L;

	for (int i = 0; i < N; i++) std::cin >> num[i];

	std::sort(num, num + N);

	for (int i = 0; i < N; ++i) {
		if (num[i] <= L) ++L;
		else break;
	}
	std::cout << L;

	return 0;
}