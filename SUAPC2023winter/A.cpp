#include <iostream>
#include <algorithm>

struct Info { 
	std::string record, team; 
	bool operator<(const Info& r) const {
		return record < r.record;
	}
} infos[8];
int score[] = { 10, 8, 6, 5, 4, 3, 2, 1 };

int main() {
	int R = 0, B = 0;
	for (int i = 0; i < 8; ++i) {
		std::cin >> infos[i].record >> infos[i].team;
	}
	std::sort(infos, infos + 8);
	for (int i = 0; i < 8; ++i) {
		(infos[i].team == "R" ? R : B) += score[i];
	}
	std::cout << (R > B ? "Red" : "Blue");
}