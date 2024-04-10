#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 500'000;
const int INF = 2e9;
int pos[LEN], even[LEN], odd[LEN];
int N, ie, io;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i];
		(pos[i] & 1 ? odd[io++] : even[ie++]) = pos[i];
	}
	int dist_e = INF, dist_o = INF;
	if (ie < 2 && io < 2) dist_e = -1;
	else {
		if (ie > 1) {
			std::sort(even, even + ie);
			for (int i = 0; i < ie - 1; ++i)
				dist_e = std::min(dist_e, even[i + 1] - even[i]);
		}
		if (io > 1) {
			std::sort(odd, odd + io);
			for (int i = 0; i < io - 1; ++i)
				dist_e = std::min(dist_e, odd[i + 1] - odd[i]);
		}
	}
	if (!ie || !io) dist_o = -1;
	else {
		std::sort(pos, pos + N);
		int l_even = even[0], l_odd = odd[0];
		for (int i = 0; i < N; ++i) {
			if (pos[i] & 1) {
				if (pos[i] > l_even) dist_o = std::min(dist_o, pos[i] - l_even);
				l_odd = pos[i];
			}
			else {
				if (pos[i] > l_odd) dist_o = std::min(dist_o, pos[i] - l_odd);
				l_even = pos[i];
			}
		}
	}
	std::cout << dist_e << ' ' << dist_o;
}