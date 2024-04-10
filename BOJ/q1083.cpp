#include <iostream>

int a[50];
int N, S;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> a[i];
	std::cin >> S;

	for (int i = 0, j, m; i < N && S; ++i) {
		for (j = m = i; j < N && j - i <= S; ++j) {
			if (a[j] > a[m]) m = j;
		}
		for (int k = m; k > i; --k) std::swap(a[k], a[k - 1]);
		S -= m - i;
	}
	for (int i = 0; i < N; ++i) std::cout << a[i] << ' ';
}