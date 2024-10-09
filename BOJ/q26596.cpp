#include <iostream>
#include <map>

inline bool golden_ratio(int a, int b) { return (int)(1.618 * a) == b; }
int main() {
	std::map<std::string, int> cocktail;
	int M, x; std::string s;
	std::cin >> M;
	while (M--) {
		std::cin >> s >> x;
		if (cocktail.find(s) == cocktail.end()) cocktail[s] = 0;
		cocktail[s] += x;
	}
	for (const auto& [k, v] : cocktail) {
		for (const auto& [k2, v2] : cocktail) {
			if (k != k2 && golden_ratio(v, v2)) {
				std::cout << "Delicious!";
				return 0;
			}
		}
	}
	std::cout << "Not Delicious...";
}