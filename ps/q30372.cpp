#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

typedef long long ll;
const int LEN = 120'001;
const ll MOD = 1e17;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	p[a] += p[b]; p[b] = a;
	return 1;
}

struct Pos {
	int i;
	ll x, y;
} pos[LEN];

ll distance(const Pos& a, const Pos& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

int target[LEN]; // target[i] = j, the longest distance group
ll target_dist[LEN]; // i -> j distance

void sweep(const std::vector<Pos>& a, const std::vector<Pos>& b); // N ~ N log N
void sweep_naive(const std::vector<Pos>& a, const std::vector<Pos>& b) { // N^2
	for (const Pos& pa : a) {
		for (const Pos& pb : b) {
			ll dist = distance(pa, pb);
			int ga = find(pa.i);
			int gb = find(pb.i);
			if (dist > target_dist[ga]) {
				target[ga] = gb;
				target_dist[ga] = dist;
			}

			if (dist > target_dist[gb]) {
				target[gb] = ga;
				target_dist[gb] = dist;
			}
		}
	}
}

struct E {
	int u, v;
	ll d;
	bool operator<(const E& r) const { return d > r.d; }
};

void solve() {
	memset(p, -1, sizeof p);
	int N;
	ll large_part = 0, small_part = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y, pos[i].i = i;
	int cnt = N;
	while (cnt > 1) {
		memset(target, -1, sizeof target);
		memset(target_dist, 0, sizeof target_dist);
		for (int d = 0; d < 20; ++d) {
			std::vector<Pos> a, b;
			for (int j = 0, k; j < N; ++j) {
				k = find(j);
				if (k & 1 << d) a.push_back(pos[j]);
				else b.push_back(pos[j]);
			}
			sweep_naive(a, b);
		}
		std::priority_queue<E> pq;
		for (int i = 0; i < N; ++i)
			if (i == find(i) && ~target[i])
				pq.push({ i, target[i], target_dist[i] });
		while (pq.size()) {
			E top = pq.top(); pq.pop();
			if (join(top.u, top.v)) {
				small_part += top.d;
				large_part += small_part / MOD;
				small_part %= MOD;
				--cnt;
			}
		}
	}
	if (large_part) {
		printf("%lld%017lld\n", large_part, small_part);
	}
	else printf("%lld\n", small_part);
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	std::cin >> T;
	while (T--) solve();
}