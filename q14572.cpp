#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 100'001;

std::vector<int> know[LEN];

int N, K, D, M, A, E, cnt[31];

struct Student { 
	int i, d; 
	bool operator<(const Student& r) const { return d < r.d; }
} students[LEN];

int main() {
	std::cin >> N >> K >> D;
	for (int i = 0; i < N; ++i) {
		std::cin >> M >> students[i].d;
		students[i].i = i;
		while (M--) {
			std::cin >> A;
			know[i].push_back(A);
		}
	}
	std::sort(students, students + N);

	int l, r, result;
	l = r = result = -1;
	while (++l < N) {
		while (r < N - 1 && students[r + 1].d <= students[l].d + D) {
			++r;
			for (const int& a : know[students[r].i])
				++cnt[a];
		}
		int ex = 0, all = 0, size = r - l + 1;
		for (int i = 1; i <= K; ++i) {
			if (cnt[i]) {
				if (cnt[i] == size) ++all;
				++ex;
			}
		}
		E = (ex - all) * size;
		std::cout << l << " ~ " << r << ": " << E << '\n';
		result = std::max(result, E);

		for (const int& a : know[students[l].i])
			--cnt[a];
	}
	std::cout << result;
}