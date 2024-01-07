#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
const int LEN = 500'000;

int N;

struct Menu { 
	int x, y, i;
	bool operator<(const Menu& r) const {
		return x == r.x ? y < r.y : x < r.x;
	}
} lunch[LEN], dinner[LEN];

bool used[LEN];

struct E {
	ll S;
	int i;
	bool operator<(const E& r) const { return S > r.S; }
};
std::priority_queue<E> lq, dq;
bool merged[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N * 2; ++i) {
		std::cin >> lunch[i].x >> lunch[i].y;
		lunch[i].i = dinner[i].i = i;
		dinner[i].x = lunch[i].y;
		dinner[i].y = lunch[i].x;
	}
	std::sort(lunch, lunch + N * 2);
	std::sort(dinner, dinner + N * 2);
	ll cost = 0;
	for (int i = 0, j, l = 0, d = 0; i < N; ++i) {
		// lunch
		while (used[lunch[l].i]) ++l;
		used[lunch[l].i] = 1;
		while (lq.size() && merged[lq.top().i]) lq.pop();
		if (lq.size()) {
			ll aug = lq.top().S;
			j = lq.top().i;
			if (lunch[l].y + aug < lunch[l].x) { // augmenting path found
				lq.pop();
				cost += aug + lunch[l].y;
				merged[j] = 1;
				dq.push({ aug - lunch[l].x + lunch[l].y, lunch[l].i });
			}
			else {
				cost += lunch[l].x;
				dq.push({ -lunch[l].x + lunch[l].y, lunch[l].i });
			}
		}
		else {
			cost += lunch[l].x;
			dq.push({ -lunch[l].x + lunch[l].y, lunch[l].i });
		}

		// dinner
		while (used[dinner[d].i]) ++d;
		used[dinner[d].i] = 1;
		while (dq.size() && merged[dq.top().i]) dq.pop();
		if (dq.size()) {
			ll aug = dq.top().S;
			j = dq.top().i;
			if (dinner[d].y + aug < dinner[d].x) { // augmenting path found
				dq.pop();
				cost += aug + dinner[d].y;
				merged[j] = 1;
				lq.push({ aug - dinner[d].x + dinner[d].y, dinner[d].i });
			}
			else {
				cost += dinner[d].x;
				lq.push({ -dinner[d].x + dinner[d].y, dinner[d].i });
			}
		}
		else {
			cost += dinner[d].x;
			lq.push({ -dinner[d].x + dinner[d].y, dinner[d].i });
		}
		std::cout << cost << '\n';
	}
}