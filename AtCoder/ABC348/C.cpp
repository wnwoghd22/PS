#include <iostream>
#include <algorithm>
#include <map>

std::map<int, int> taste;
int N, A, C;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A >> C;
		if (taste.find(C) == taste.end()) taste[C] = A;
		else taste[C] = std::min(taste[C], A);
	}
	int ret = 0;
	for (const auto& e : taste) {
		if (e.second > ret) 
			ret = e.second;
	}
	std::cout << ret;
}