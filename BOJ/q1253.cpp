#include <iostream>
#include <unordered_map>

const int LEN = 2000;
std::unordered_map<int, int> map;

int N, M, A[LEN];

int main() {
	std::cin >> N;
	map.reserve(N);

	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		if (map.find(A[i]) == map.end()) map[A[i]] = 1;
		else ++map[A[i]];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map.find(A[i] - A[j]) != map.end()) {
				if (A[i] == 0) {
					if (A[j] == 0 && map[0] < 3) continue;
				}
				else {
					if (A[j] == 0 && map[A[i]] < 2) continue;
					if (A[j] == A[i] && map[A[i]] < 2) continue;
					if (A[j] * 2 == A[i] && map[A[j]] < 2) continue;
				}
				++M;
				break;
			}
		}
	}
	std::cout << M;
}