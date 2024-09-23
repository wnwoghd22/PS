#include <iostream>
#include <algorithm>

int arr[1000];

int main() {
	int N, cost = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> arr[i];
	std::sort(arr, arr + N);

	cost += arr[N - 1] - arr[0];
	for (int i = 1; i < N; ++i) cost += arr[i] - arr[i - 1];

	std::cout << cost;
}