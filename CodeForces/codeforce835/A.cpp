#include <iostream>
#include <algorithm>

int T, arr[3];

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> arr[0] >> arr[1] >> arr[2];
		std::sort(arr, arr + 3);
		std::cout << arr[1] << '\n';
	}
}