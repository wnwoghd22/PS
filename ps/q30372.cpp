#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define __PS_DEBUG__
#undef __PS_DEBUG__

typedef long long ll;
const int LEN = 120'001;
const ll MOD = 1e17;

int N, p[LEN];
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

ll f(int i, int j) {
	if (j < i) return -i -N +j;
	if (j >= N && j - N >= i) return -i -j;

	return distance(pos[i], pos[j % N]);
}
ll smawk_maxima[LEN];

std::vector<int> smawk(const std::vector<int>& row, const std::vector<int>& col) {
	if (row.empty() || col.empty()) return {};
	if (row.size() == 1) {
		std::vector<int> ans = { 0 };
		int r = row[0];
		for (const int& c : col) {
			int ga = find(r), gb = find(c % N);
			ll dist = f(r, c);
			if (dist > smawk_maxima[r]) {
				ans[0] = c;
				smawk_maxima[r] = dist;
			}
			if (dist > target_dist[ga]) {
				target[ga] = gb;
				target_dist[ga] = dist;
			}
		}
		return ans;
	}

	// reduce
	std::vector<int> cols;
	for (const int& j : col) {
		if (cols.empty()) cols.push_back(j);
		else {
			int i;
			while (cols.size()) {
				i = cols.size() - 1;
				ll top = f(row[i], cols.back());
				ll next = f(row[i], j);
				// if (!~top && !~next) break;
				if (top > next) break;
#ifdef __PS_DEBUG__
				std::cout << "pop " << cols.back() << '\n';
				std::cout << "	row: " << i << ", (top, next): " << top << ",'" << next << '\n';
#endif
				cols.pop_back();
			}
			if (cols.size() < row.size()) cols.push_back(j);
		}
	}

	std::vector<int> rows;
	for (int i = 0; i < row.size(); i += 2) rows.push_back(row[i]);

	std::vector<int> ret = smawk(rows, cols);

#ifdef __PS_DEBUG__
	std::cout << "cols\n";
	for (const int& c : cols) std::cout << c << ' ';
	std::cout << '\n';
#endif

	// linear search
	std::vector<int> ans(row.size());
	for (int i = 0; i < ret.size(); ++i) ans[i * 2] = ret[i];
	for (int i = 1, j = 0; i < row.size(); i += 2) {
		int s = ans[i - 1];
		int e = i + 1 < ans.size() ? ans[i + 1] : cols.back();
		int r = row[i];

		while (cols[j] < s) ++j;
		ans[i] = s;
		
		while (1) {
			int c = cols[j] % N;
			int ga = find(r), gb = find(c);
			ll dist = f(r, cols[j]);
			if (dist > smawk_maxima[r]) {
				ans[i] = cols[j];
				smawk_maxima[r] = dist;
			}
			if (dist > target_dist[ga]) {
				target[ga] = gb;
				target_dist[ga] = dist;
			}
			if (cols[j] >= e) break;
			++j;
		}
#ifdef __PS_DEBUG__
		std::cout << "assign minima: " << r << ' ' << smawk_maxima[r] << '\n';
#endif
	}
	return ans;
}

#ifdef __PS_DEBUG__
ll brute_maxima[LEN];
void print_maxima(const std::vector<int>& row, const std::vector<int>& col) {
	if (row.empty() || col.empty()) return;
	std::cout << "print maxima\n";
	for (const int& r : row) std::cout << r << ' '; std::cout << '\n';
	for (const int& c : col) std::cout << c << ' '; std::cout << '\n';

	memset(brute_maxima, 0, sizeof brute_maxima);
	for (const int& r : row) {
		for (const int& c : col) {
			std::cout << f(r, c) << ' ';
			if (f(r, c) > brute_maxima[r]) brute_maxima[r] = f(r, c);
		}
		std::cout << '\n';
	}
	for (const int& r : row) {
		std::cout << r << ' ' << brute_maxima[r] << ' ' << smawk_maxima[r] << '\n';
		if (brute_maxima[r] != smawk_maxima[r]) {
			std::cout << "	problem detected!: " << r << " ----------------------------------------------\n";
			std::cout << "	(brute, smawk) = " << brute_maxima[r] << ' ' << smawk_maxima[r] << '\n';
		}
	}
}
#endif

void sweep(const std::vector<Pos>& a, const std::vector<Pos>& b) { // N ~ N log N
	std::vector<int> row, col;

	for (const Pos& p : a) row.push_back(p.i);
	for (const Pos& p : b) col.push_back(p.i);
	for (const Pos& p : b) col.push_back(p.i + N);

	smawk(row, col);

#ifdef __PS_DEBUG__
	print_maxima(row, col);
#endif

	memset(smawk_maxima, 0, sizeof smawk_maxima);

	row.clear();
	col.clear();

	for (const Pos& p : b) row.push_back(p.i);
	for (const Pos& p : a) col.push_back(p.i);
	for (const Pos& p : a) col.push_back(p.i + N);

	smawk(row, col);

#ifdef __PS_DEBUG__
	print_maxima(row, col);
#endif

	memset(smawk_maxima, 0, sizeof smawk_maxima);
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
	ll large_part = 0, small_part = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y, pos[i].i = i;
	int cnt = N;
	while (cnt > 1) {
#ifdef __PS_DEBUG__
		std::cout << "cnt: " << cnt << "\n";
#endif
		memset(target, -1, sizeof target);
		memset(target_dist, 0, sizeof target_dist);

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

		if (pq.empty()) {
			std::cout << "panic! no edges.";
			break;
		}

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
	freopen("output.txt", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	int T;
	std::cin >> T;
	while (T--) solve();
}