#include <iostream>

int arr[100'000];
int N, M;

int binary_search(int l, int r) {
	int result = N * l, mid, count;

	while (l <= r) {
		mid = (l + r) / 2, count = 1;

		for (int current = 0, i = 0; i < N; ++i) {
			if (current + arr[i] > mid) {
				current = arr[i];
				count++;
			}
			else current += arr[i];
		}

		if (count <= M) {
			result = std::min(result, mid);
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return result;
}

int main() {
	int max = 0, sum = 0;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> arr[i];
		sum += arr[i];
		max = std::max(max, arr[i]);
	}

	std::cout << binary_search(max, sum);
}