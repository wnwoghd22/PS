#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 300'000;

struct E {
	int i, A;
	bool operator<(const E& r) const { return A < r.A; }
} LR[LEN], UD[LEN];

struct Pos {
	int x, y;
	int cw, ccw; // linked list
} pos[LEN];
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (ll)(d2.x - d1.x) * (d3.y - d2.y) - (ll)(d2.y - d1.y) * (d3.x - d2.x);
}

int N, L, R, U, D;
char S[LEN];
bool visited[LEN];
int order[LEN];
ll ans[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i].x >> pos[i].y;
		LR[i] = { i, pos[i].x };
		UD[i] = { i, pos[i].y };
	
	}
	std::cin >> S;
	std::sort(LR, LR + N);
	std::sort(UD, UD + N);
	L = 0, R = N - 1;
	D = 0, U = N - 1;
	for (int i = 0; i < N - 2; ++i) {
		if (S[i] == 'L') {
			while (L <= R && visited[LR[L].i]) ++L;
			order[i] = LR[L].i;
		}
		if (S[i] == 'R') {
			while (L <= R && visited[LR[R].i]) --R;
			order[i] = LR[R].i;
		}
		if (S[i] == 'D') {
			while (D <= U && visited[UD[D].i]) ++D;
			order[i] = UD[D].i;
		}
		if (S[i] == 'U') {
			while (D <= U && visited[UD[U].i]) --U;
			order[i] = UD[U].i;
		}
		visited[order[i]] = 1;
	}

	R = LR[0].i; L = LR[N - 1].i;
	U = UD[0].i; D = UD[N - 1].i;
	for (int i = 0; i < N; ++i) {
		if (!visited[i]) {
			if (pos[i].x < pos[L].x) L = i;
			if (pos[i].x > pos[R].x) R = i;
			if (pos[i].y < pos[D].y) D = i;
			if (pos[i].y > pos[U].y) U = i;
		}
	}
	pos[R].cw = pos[R].ccw = L;
	pos[L].cw = pos[L].ccw = R;
	for (int i = N - 3, j, k; i >= 0; --i) {
		if (S[i] == 'L') j = L;
		if (S[i] == 'R') j = R;
		if (S[i] == 'U') j = U;
		if (S[i] == 'D') j = D;
		k = order[i];

		ll area;
		pos[k].cw = pos[k].ccw = j;
		/*
		 * to calculate time comlpexity:
		 * when adding area, a pos is popped from hull.
		 * when a pos is popped, then color it red.
		 * after all, how many red pos exists?
		 * at most N - 3.
		 * while loop below seems nested O(N^2),
		 * but actually O(N)
		 */
		while ((area = cross(pos[k], pos[pos[k].ccw], pos[pos[pos[k].ccw].ccw])) > 0) {
			ans[i] += area;
			pos[k].ccw = pos[pos[k].ccw].ccw;
		}
		while ((area = cross(pos[k], pos[pos[k].cw], pos[pos[pos[k].cw].cw])) < 0) {
			ans[i] -= area;
			pos[k].cw = pos[pos[k].cw].cw;
		}
		pos[pos[k].ccw].cw = k;
		pos[pos[k].cw].ccw = k;

		if (pos[k].x < pos[L].x) L = k;
		if (pos[k].x > pos[R].x) R = k;
		if (pos[k].y < pos[D].y) D = k;
		if (pos[k].y > pos[U].y) U = k;

		ans[i] += ans[i + 1];
	}
	for (int i = 0; i < N - 2; ++i) std::cout << (ans[i] >> 1) << '.' << 5 * (ans[i] & 1) << '\n';
} 