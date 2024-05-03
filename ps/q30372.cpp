#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define __PS_DEBUG__
// #undef __PS_DEBUG__

typedef long long ll;
const int LEN = 120'001;
const ll MOD = 1e17;
const ll INF = 1e17;

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

ll f(int i, int j) { return distance(pos[i], pos[j]); }

#ifdef __PS_DEBUG__
ll brute_maxima[LEN], smawk_maxima[LEN];
#endif


void smawk(const std::vector<int>& a, const std::vector<int>& b) {
	if (a.empty() || b.empty()) return;

#ifdef __PS_DEBUG__
	std::cout << "		smawk: " << a.size() << ' ' << b.size() << '\n';
#endif

	// reduce
	std::vector<int> cols;
	for (const int& j : b) {
		if (cols.empty()) cols.push_back(j);
		else {
			int i;
			while (cols.size()) {
				i = cols.size() - 1;
				if (f(a[i], cols.back()) > f(a[i], j)) break;
				cols.pop_back();
			}
			if (cols.size() < a.size()) cols.push_back(j);
		}
	}

	// interpolate
	std::vector<int> rows;
	for (int i = 1; i < a.size(); i += 2) rows.push_back(a[i]);

	smawk(rows, cols);

	// linear search
	for (int i = 0, j = 0; i < a.size(); i += 2) {
		while (j + 1 < cols.size() && f(a[i], cols[j]) <= f(a[i], cols[j + 1])) ++j;
		int ga = find(a[i]), gb = find(cols[j]);
		ll dist = f(a[i], cols[j]);
		if (dist > target_dist[ga]) {
			target[ga] = gb;
			target_dist[ga] = dist;
		}
#ifdef __PS_DEBUG__
		smawk_maxima[a[i]] = dist;
#endif
	}
}

void sweep(const std::vector<Pos>& a, const std::vector<Pos>& b) { // N ~ N log N
#ifdef __PS_DEBUG__
	std::cout << "	sweep\n";
#endif
	std::vector<int> row, col;

	for (const Pos& p : a) row.push_back(p.i);
	for (const Pos& p : b) col.push_back(p.i);
	for (const Pos& p : b) col.push_back(p.i);

	smawk(row, col);

#ifdef __PS_DEBUG__
	std::cout << "	table: \n";
	for (const int& r : row) {
		std::cout << r << ' ';
		ll max = 0;
		for (const int& c : col) {
			std::cout << f(r, c) << ' ';
			if (max < f(r, c)) max = f(r, c);
		}
		std::cout << "max: " << (brute_maxima[r] = max) << '\n';
	}
	std::cout << "	check...\n";
	for (const int& r : row) {
		if (brute_maxima[r] != smawk_maxima[r]) {
			std::cout << "		problem detected!\n";
			std::cout << "			brute, smawk: " << brute_maxima[r] << ' ' << smawk_maxima[r] << '\n';
		}
	}
#endif

	row.clear();
	col.clear();

	for (const Pos& p : b) row.push_back(p.i);
	for (const Pos& p : a) col.push_back(p.i);
	for (const Pos& p : a) col.push_back(p.i);

	smawk(row, col);

#ifdef __PS_DEBUG__
	std::cout << "	table: \n";
	for (const int& r : row) {
		std::cout << r << ' ';
		ll max = 0;
		for (const int& c : col) {
			std::cout << f(r, c) << ' ';
			if (max < f(r, c)) max = f(r, c);
		}
		std::cout << "max: " << (brute_maxima[r] = max) << '\n';
	}
	std::cout << "	check...\n";
	for (const int& r : row) {
		std::cout << "	minima[" << r << "] = " << smawk_maxima[r] << '\n';
		if (brute_maxima[r] != smawk_maxima[r]) {
			std::cout << "		problem detected!: " << r << "\n";
			std::cout << "			brute, smawk: " << brute_maxima[r] << ' ' << smawk_maxima[r] << '\n';
		}
	}
#endif
}
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
#ifdef __PS_DEBUG__
		std::cout << "cnt: " << cnt << '\n';
#endif
		for (int d = 0; d < 20; ++d) {
			std::vector<Pos> a, b;
			for (int j = 0, k; j < N; ++j) {
				k = find(j);
				if (k & 1 << d) a.push_back(pos[j]);
				else b.push_back(pos[j]);
			}
			sweep(a, b);
			// sweep_naive(a, b);
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