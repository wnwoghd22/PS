#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int A[200001];

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int N, X;
		std::cin >> N >> X;

		if (N % X) std::cout << -1 << '\n';
		else {
			std::vector<int> p;
			for (int i = 1; i <= sqrt(N); ++i) {
				if (N % i == 0) {
					p.push_back(i);
					if (i != N / i) p.push_back(N / i);
				}
			}
			std::sort(p.begin(), p.end());

			int j = 0;
			std::cout << X << ' ';
			for (int i = 2; i < N; ++i) {
				if (i == X) {
					while (true) {
						if (p[j] > X && (p[j] % X) == 0) break;
						if (j == p.size() - 1) break;
						++j;
					}
					X = p[j];
					std::cout << X << ' ';
				}
				else std::cout << i << ' ';
			}
			std::cout << 1 << '\n';
		}
	}
}