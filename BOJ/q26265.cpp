#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<std::string, std::string> pss;
bool comp(const pss& l, const pss& r) {
	if (l.first == r.first) return l > r;
	return l < r;
}

int main() {
	std::vector<pss> v;
	int N; std::string mento, menti;
	std::cin >> N;
	while (N--) {
		std::cin >> mento >> menti;
		v.push_back({ mento, menti });
	}
	std::sort(v.begin(), v.end(), comp);
	for (const pss& e : v) {
		std::cout << e.first << ' ' << e.second << '\n';
	}
}