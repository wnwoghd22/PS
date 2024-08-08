#include <iostream>
#include <algorithm>

/* algorithm
 * 
 * - make linked-list that links elements a_i and a_j if a_i == a_j
 * - make min seg tree of left pointers and max seg tree of right pointers of linked list.
 * - check each query that
 * - right_poninters.max(s, e) > e and
 * - left_pointers.min(s, e) < s
 * - if both are true, then every elements between s and e are unique.
 * - if not, then find arbitrary and print.
 */

const int LEN = 1'000'001;

int M, Q, K[LEN];
int left[LEN], right[LEN]; // pointers

struct E {
	int i, a;
	bool operator<(const E& o) const {
		return a == o.a ? i < o.i : a < o.a;
	}
} e[LEN];

void solve() {
	for (int i = 0; i < M; ++i) {
		std::cin >> K[i];
		e[i] = { i, K[i] };
	}
	std::sort(e, e + M);

	// make linked list
	left[e[0].i] = -1;
	for (int i = 1; i < M; ++i) {
		if (e[i].a != e[i - 1].a) left[e[i].i] = -1;
		else left[e[i].i] = e[i - 1].i;
	}
	right[e[0].i] = M;
	for (int i = M - 2; i >= 0; --i) {
		if (e[i].a != e[i + 1].a) right[e[i].i] = M;
		else right[e[i].i] = e[i + 1].i;
	}

	for (int q = 0; q < Q; ++q) {

	}

}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> M >> Q;
		if (!M && !Q) break;
		solve();
	}
}