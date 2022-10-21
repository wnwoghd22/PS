#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

struct Jewel {
	int weight, value;
	bool operator()(Jewel& a, Jewel& b) {
		return a.value < b.value ? true : (a.value == b.value && a.weight > b.weight);
	}
};

int main() {
	std::priority_queue<Jewel, std::vector<Jewel>, Jewel> j;
	std::map<int, int> s;
	int N, K;
	long long result = 0;
	std::cin >> N >> K;
	while (N--) {
		int m, v;
		std::cin >> m >> v;
		j.push({ m, v });
	}
	while (K--) {
		int c;
		std::cin >> c;
		if (s.find(c) == s.end()) s[c] = 1;
		else s[c]++;
	}

	while (!s.empty() && !j.empty()) {
		Jewel top = j.top(); j.pop();
		auto lower = s.lower_bound(top.weight);
		if (lower != s.end()) {
			result += top.value;
			lower->second--;
			if (!lower->second) s.erase(lower);
		}
	}
	std::cout << result;
}