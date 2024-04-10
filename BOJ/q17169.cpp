#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
const int LEN = 200;

int N;

struct Menu {
	int x, y, i;
	bool operator<(const Menu& r) const {
		return x == r.x ? y < r.y : x < r.x;
	}
} lunch[LEN], dinner[LEN];

bool used[LEN];

std::priority_queue<ll> lq, dq;

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
	for (int i = 0, l = 0, d = 0; i < N; ++i) {
		// lunch
		while (l < N * 2 && used[lunch[l].i]) ++l;
		while (d < N * 2 && used[dinner[d].i]) ++d;
		if (l < N * 2 && d < N * 2 && lq.size() && dinner[d].x - lq.top() < lunch[l].x) { // augmenting path found
			used[dinner[d].i] = 1;
			ll aug = -lq.top();
			lq.pop();
			cost += aug + dinner[d].x;
			lq.push(dinner[d].x - dinner[d].y);
			dq.push(aug);
		}
		else if (l >= N * 2) {
			used[dinner[d].i] = 1;
			ll aug = -lq.top();
			lq.pop();
			cost += aug + dinner[d].x;
			lq.push(dinner[d].x - dinner[d].y);
			dq.push(aug);
		}
		else {
			used[lunch[l].i] = 1;
			cost += lunch[l].x;
			dq.push(lunch[l].x - lunch[l].y);
		}

		// dinner
		while (l < N * 2 && used[lunch[l].i]) ++l;
		while (d < N * 2 && used[dinner[d].i]) ++d;
		if (l < N * 2 && d < N * 2 && dq.size() && lunch[l].x - dq.top() < dinner[d].x) { // augmenting path found
			used[lunch[l].i] = 1;
			ll aug = -dq.top();
			dq.pop();
			cost += aug + lunch[l].x;
			dq.push(lunch[l].x - lunch[l].y);
			lq.push(aug);
		}
		else if (d >= N * 2) {
			used[lunch[l].i] = 1;
			ll aug = -dq.top();
			dq.pop();
			cost += aug + lunch[l].x;
			dq.push(lunch[l].x - lunch[l].y);
			lq.push(aug);
		}
		else {
			used[dinner[d].i] = 1;
			cost += dinner[d].x;
			lq.push(dinner[d].x - dinner[d].y);
		}

		std::cout << cost << '\n';
	}
}