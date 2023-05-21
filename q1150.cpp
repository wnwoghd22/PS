#include <iostream>
#include <queue>

const int LEN = 100'001;

struct Segment {
	int c, l, r;
	bool operator<(const Segment& rhs) const { return c > rhs.c; }
} s[LEN];
int N, K, Dl, Dr, i, result;
std::priority_queue<Segment> pq;

int main() {
	std::cin >> N >> K >> Dl;
	for (i = 1; i < N; ++i, Dl = Dr) {
		std::cin >> Dr;
		s[i].c = Dr - Dl;
		s[i].l = i - 1;
		s[i].r = i + 1;
		pq.push({ s[i].c, i, i + 1 });
	}
	s[N] = { 0, N - 1, N + 1 };

	for (i = 0; i < K;) {
		Segment cur = pq.top(); pq.pop();
		std::cout << cur.l << ' ' << cur.r << '\n';
		if (cur.l >= 1 && cur.r <= N && cur.l == s[cur.r].l && cur.r == s[cur.l].r) { // augment path
			std::cout << "augment\n";
			result += cur.c;
			++i;
			int nl = s[cur.l].l, nr = s[cur.r].r;
			s[nl].c = s[nl].c + s[cur.r].c - cur.c;
			cur.c = s[nl].c;
			cur.l = nl; cur.r = nr;
			s[nl].r = nr;
			s[nr].l = nl;
			pq.push(cur);
		}
	}
	std::cout << result;
}