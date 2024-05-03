#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define __PS_DEBUG__
// #undef __PS_DEBUG__

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

ll f(
	const std::vector<Pos>& row, const std::vector<Pos>& col, 
	int i, int j) {
	if (j < i) return -1;
	if (j >= col.size() && j - col.size() >= i) return -1;

	return distance(row[i], col[j % col.size()]);
}
ll smawk_maxima[LEN];

#ifdef __PS_DEBUG__
ll brute_maxima[LEN];
void print_maxima(
	const std::vector<Pos>& a, const std::vector<Pos>& b,
	const std::vector<int>& row, const std::vector<int>& col
) {
	if (a.empty() || b.empty()) return;
	std::cout << "table: \n";
	for (int i = 0; i < row.size(); ++i) {
		ll max = 0;
		for (int j = 0; j < col.size(); ++j) {
			ll cur = f(a, b, i, j);
			std::cout << cur << ' ';
			if (max < cur) max = cur;
		}
		std::cout << "max: " << (brute_maxima[i] = max) << '\n';
		std::cout << '\n';
	}
	std::cout << "	check...\n";
	for (const int& r : row) {
		std::cout << "	minima[" << r << "] = " << smawk_maxima[r] << '\n';
		if (brute_maxima[r] != smawk_maxima[r]) {
			std::cout << "		problem detected!: " << r << "\n";
			std::cout << "			brute, smawk: " << brute_maxima[r] << ' ' << smawk_maxima[r] << '\n';
		}
	}
	memset(brute_maxima, 0, sizeof brute_maxima);
}
#endif

std::vector<int> smawk(
	const std::vector<Pos>& row, const std::vector<Pos>& col,
	const std::vector<int>& a, const std::vector<int>& b) {
	if (a.empty() || b.empty()) return {};
#ifdef __PS_DEBUG__
	std::cout << "smawk: " << a.size() << ' ' << b.size() << '\n';
#endif
	if (a.size() == 1) {
		std::vector<int> ans = { 0 };
		int r = a[0];
		for (int i = 0; i < b.size(); ++i) {
			int c = b[i] % col.size();
			int ga = find(row[r].i), gb = find(col[c].i);
			ll dist = f(row, col, r, b[i]);
			if (dist > smawk_maxima[r]) {
				ans[0] = b[i];
				smawk_maxima[r] = dist;
			}
			if (dist > target_dist[ga]) {
				target[ga] = gb;
				target_dist[ga] = dist;
			}
		}
#ifdef __PS_DEBUG__
			std::cout << "maxima[" << r << "] = " << smawk_maxima[r] << "\n\n";
#endif
		return ans;
	}

	// reduce
	std::vector<int> cols;
	for (const int& j : b) {
		if (cols.empty()) cols.push_back(j);
		else {
			int i;
			while (cols.size()) {
				i = cols.size() - 1;
				ll top = f(row, col, a[i], cols.back());
				ll next = f(row, col, a[i], j);
				if (top > next) break;
				cols.pop_back();
			}
			if (cols.size() < a.size()) cols.push_back(j);
		}
	}

	std::vector<int> rows;
	for (int i = 0; i < a.size(); i += 2) rows.push_back(a[i]);

	std::cout << "recursive\n";
	std::vector<int> ret = smawk(row, col, rows, cols);
	std::vector<int> ans(a.size());
	for (int i = 0; i < ret.size(); ++i) ans[i * 2] = ret[i];

	// linear search
#ifdef __PS_DEBUG__
	std::cout << "linear search: " << a.size() << ' ' << b.size() << '\n';
	std::cout << "ret:\n";
	for (const int& idx : ret) std::cout << idx << ' ';
	std::cout << '\n';
	std::cout << "cols:\n";
	for (const int& idx : cols) std::cout << idx << ' ';
	std::cout << '\n';
#endif
	for (int i = 1, j = 0; i < a.size(); i += 2) {
		int s = ans[i - 1];
		int e = i + 1 < ans.size() ? ans[i + 1] : cols.back();
		int r = a[i];
#ifdef __PS_DEBUG__
		std::cout << "row: " << r << '\n';
		std::cout << "range: " << s << ' ' << e << '\n';
#endif
		while (b[j] < s) ++j;
		ans[i] = s;
		
		while (1) {
			std::cout << j << ' ';
			int c = col[b[j] % col.size()].i;
			int ga = find(row[r].i), gb = find(col[b[j] % col.size()].i);
			ll dist = f(row, col, r, b[j]);
			if (dist > smawk_maxima[r]) {
				ans[i] = b[j];
				smawk_maxima[r] = dist;
			}
			if (dist > target_dist[ga]) {
				target[ga] = gb;
				target_dist[ga] = dist;
			}
			if (b[j] >= e) break;
			++j;
		}
		std::cout << '\n';
#ifdef __PS_DEBUG__
			std::cout << "maxima[" << r << "] = " << smawk_maxima[r] << '\n';
#endif
	}
#ifdef __PS_DEBUG__
	std::cout << '\n';
#endif
	return ans;
}

void sweep(const std::vector<Pos>& a, const std::vector<Pos>& b) { // N ~ N log N
	std::vector<int> row, col;

#ifdef __PS_DEBUG__
	std::cout << "	sweep\n";
#endif

	for (int i = 0; i < a.size(); ++i) row.push_back(i);
	for (int i = 0; i < b.size() * 2; ++i) col.push_back(i);

	smawk(a, b, row, col);

#ifdef __PS_DEBUG__
	print_maxima(a, b, row, col);
#endif
	memset(smawk_maxima, 0, sizeof smawk_maxima);

	row.clear();
	col.clear();

	for (int i = 0; i < b.size(); ++i) row.push_back(i);
	for (int i = 0; i < a.size() * 2; ++i) col.push_back(i);

	smawk(b, a, row, col);

#ifdef __PS_DEBUG__
	print_maxima(b, a, row, col);
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
	int N;
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