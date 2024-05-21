#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long ll;
const int LEN = 200'010;

struct Fenwick {
	ll t[LEN];
	ll sum(int i) {
		ll ret = 0;
		while (i > 0) {
			ret += t[i];
			i -= i & -i;
		}
		return ret;
	}
	void update(int i, ll d) {
		while (i < LEN) {
			t[i] += d;
			i += i & -i;
		}
	}
} sum, cnt;

struct Query { 
	int l, r;
	ll sum, cnt;
} q[LEN];

struct Project {
	int l, r;
	int a, b;
	ll s;
} p[LEN];

int N, Q, P[LEN];

struct Event {
	int t;
	int i, d;
	bool operator<(const Event& r) const { return t < r.t; }
} e[LEN * 2];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> P[i];

	std::vector<int> cur;

	std::cin >> Q;
	for (int i = 0; i < Q; ++i) {
		std::cin >> p[i].l >> p[i].r >> p[i].a >> p[i].b >> p[i].s;
		e[i << 1] = { p[i].l - 1, i, -1 };
		e[i << 1 | 1] = { p[i].r, i, +1 };
		q[i].l = p[i].a;
		q[i].r = p[i].b;
		cur.push_back(i);
	}
	std::sort(e, e + Q * 2);

	while (cur.size()) {
		memset(sum.t, 0, sizeof sum.t);
		memset(cnt.t, 0, sizeof cnt.t);
		int j = 0;
		while (j < Q * 2 && e[j].t == 0) {
			q[e[j].i].sum = q[e[j].i].cnt = 0;
			++j;
		}

		for (int i = 1; i <= N; ++i) {
			sum.update(P[i], P[i]);
			cnt.update(P[i], 1);

			while (j < Q * 2 && e[j].t == i) {
				int x = e[j].i;
				int m = q[x].l + q[x].r >> 1;
				if (e[j].d == 1) {
					q[x].cnt += cnt.sum(p[x].b) - cnt.sum(m - 1);
					q[x].sum += sum.sum(p[x].b) - sum.sum(m - 1);
				}
				else {
					q[x].cnt = cnt.sum(m - 1) - cnt.sum(p[x].b);
					q[x].sum = sum.sum(m - 1) - sum.sum(p[x].b);
				}
				++j;
			}
		}

		std::vector<int> nxt;
		for (const int& i : cur) {
			int m = q[i].l + q[i].r >> 1;			
			if (q[i].sum >= q[i].cnt * p[i].s) q[i].r = m;
			else q[i].l = m + 1;

			if (q[i].l < q[i].r) nxt.push_back(i);
		}
		cur.swap(nxt);
	}

	memset(sum.t, 0, sizeof sum.t);
	memset(cnt.t, 0, sizeof cnt.t);
	int j = 0;
	while (j < Q * 2 && e[j].t == 0) {
		q[e[j].i].sum = q[e[j].i].cnt = 0;
		++j;
	}

	for (int i = 1; i <= N; ++i) {
		sum.update(P[i], P[i]);
		cnt.update(P[i], 1);

		while (j < Q * 2 && e[j].t == i) {
			int x = e[j].i;
			if (e[j].d == 1) {
				q[x].cnt += cnt.sum(p[x].b) - cnt.sum(q[x].r - 1);
				q[x].sum += sum.sum(p[x].b) - sum.sum(q[x].r - 1);
			}
			else {
				q[x].cnt = cnt.sum(q[x].r - 1) - cnt.sum(p[x].b);
				q[x].sum = sum.sum(q[x].r - 1) - sum.sum(p[x].b);
			}
			++j;
		}
	}

	for (int i = 0; i < Q; ++i) {
		int ans = q[i].sum >= q[i].cnt * p[i].s ? q[i].cnt : 0;
		if (ans && q[i].r > p[i].a) {
			int d = (q[i].sum - p[i].s * q[i].cnt) / (p[i].s - q[i].r + 1);
			ans += d;
		}
		std::cout << ans << '\n';
	}
}