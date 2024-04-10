#include <iostream>
#include <algorithm>

int N, s1, s2, arr[100];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> arr[i], arr[i] *= -1;
	std::sort(arr, arr + N);

	for (int i = 0; i < std::min(N, 42); ++i) {
		s1 -= arr[i];
		s2 += (arr[i] > -60 ? 0 :
			arr[i] > -100 ? 1 :
			arr[i] > -140 ? 2 :
			arr[i] > -200 ? 3 :
			arr[i] > -250 ? 4 : 5);
	}
	std::cout << s1 << ' ' << s2;
}