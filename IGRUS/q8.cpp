#include <iostream>

int get_score(int a, int b) {
	int n = a * b, result = 0;
	while (n > 0) {
		result += n % 10;
		n /= 10;
	}
	return result;
}

int count[1000];

int main() {
	int N, result = 0;
	std::cin >> N;
	while (N--) {
		int a;
		std::cin >> a;
		count[a]++;
	}
	for (int i = 1; i < 1000; ++i) {
		if (count[i] > 1) result = std::max(result, get_score(i, i));
		if (!count[i]) continue;
		for (int j = i + 1; j < 1000; ++j) {
			if (count[j]) result = std::max(result, get_score(i, j));
		}
	}
	std::cout << result;
}