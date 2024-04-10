#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	int N, K;
	std::vector<std::string> v;
	std::cin >> N >> K;
	while (K--) {
		std::string s;
		std::cin >> s;
		v.push_back(s);
	}
	std::sort(v.begin(), v.end());
	for (const std::string& s : v) std::cout << s << '\n';
}