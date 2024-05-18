#include <iostream>
#include <algorithm>

const int LEN = 2e5;

int N;

struct Card {
	int a, c, i;
	bool operator<(const Card& o) const {
		return a == o.a ? c < o.c : a < o.a;
	}
} cards[LEN];

int idx, remains[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> cards[i].a >> cards[i].c;
		cards[i].i = i + 1;
	}
	std::sort(cards, cards + N);
	remains[idx++] = cards[N - 1].i;
	int min_cost = cards[N - 1].c;
	for (int i = N - 2; i >= 0; --i) {
		if (cards[i].c > min_cost) continue;
		min_cost = cards[i].c;
		remains[idx++] = cards[i].i;
	}
	std::sort(remains, remains + idx);
	std::cout << idx << '\n';
	for (int i = 0; i < idx; ++i) std::cout << remains[i] << ' ';
}