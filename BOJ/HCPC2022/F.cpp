#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int, std::pair<std::string, int>> ISD;
std::vector<ISD> v;

char to_upper(char c) { return (c >= 'a' && c <= 'z') ? c - 32 : c; }

int main() {
	std::string s;
	int N, i, d;
	std::cin >> N;
	while (N--) {
		std::cin >> s >> i >> d;
		v.push_back({ i, {s, d} });
	}
	std::sort(v.begin(), v.end());
	for (auto& [i, p] : v) {
		auto& [s, d] = p;
		std::cout << to_upper(s[d - 1]);
	}
}