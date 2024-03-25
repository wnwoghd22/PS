#define _CRT_SECURE_NO_WARNINGS
#define DEBUG_PRINT 1
#undef DEBUG_PRINT

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

#include <cassert>

typedef long long ll;
const int LEN = 100'001;
const int BUY = 1;
const int SELL = 2;

int N;
int idx;
struct Node {
	int n_id, id;
	int pre, nxt;
	int v, cv, tv;
} nodes[LEN];

int NT;
struct Trade {
	int bid, sid, p, v;
	bool operator<(const Trade& r) const { return bid == r.bid ? sid < r.sid : bid < r.bid; }
} trades[LEN];
void insert_trade(int bid, int sid, int p, int v) { trades[NT++] = { bid, sid, p, v }; }

struct PriceInfo {
	int head = -1, type = -1;
	ll SV = 0;

	void exhaust(int id, int p, int is_sell) {
		int bid, sid;
		(is_sell ? sid : bid) = id;
		int cur = head;
		do {
			Node& n = nodes[cur];
			(is_sell ? bid : sid) = n.id;
			insert_trade(bid, sid, p, n.v + n.cv);
			cur = n.nxt;
		} while (cur != head);

		SV = 0;
		head = -1;
	}
	void make_trade(int id, int p, int v, int is_sell) {
		int bid, sid;
		int last_ordered = -1;
		std::map<int, int> traded;

		(is_sell ? sid : bid) = id;
		SV -= v;

		// exhaust cv
		int cur = head;
		assert(~cur);
		do {
			Node& n = nodes[cur];
			int delta = std::min(v, n.cv);

			traded[n.id] = delta;
			n.cv -= delta;
			v -= delta;
			if (!v) {
				last_ordered = n.n_id;
				break;
			}

			cur = n.nxt;
		} while (cur != head);

		if (~last_ordered) { // no cycles
			int now = head;
			bool refilled = 0;
			while (1) {
				Node& n = nodes[now];

				if (n.cv == 0) {
					if (n.n_id == last_ordered) refilled = 1;

					n.cv = std::min(n.v, n.tv);
					n.v -= n.cv;

					if (n.cv == 0 && n.v == 0) { // no volume
						Node& pre = nodes[n.pre];
						Node& nxt = nodes[n.nxt];
						pre.nxt = n.nxt;
						nxt.pre = n.pre;
					}
				}

				if (n.n_id == last_ordered) break;
				now = n.nxt;
			};
			head = now;
			if (refilled) {
				head = nodes[head].nxt;
				while (nodes[head].v + nodes[head].cv == 0) head = nodes[head].nxt;
			}
		}
		else { // cycle detected -> bs
#ifdef DEBUG_PRINT
			std::cout << "	cycle detected\n";
#endif

		}

		for (const auto& iter : traded) {
			(is_sell ? bid : sid) = iter.first;
			int volume = iter.second;
			insert_trade(bid, sid, p, volume);
		}
#ifdef DEBUG_PRINT
		std::cout << '\n';
#endif
	}
	void insert(int id, int t, int v, int tv) {
		type = t;
		Node& n = nodes[idx];
		n.n_id = idx++;
		SV += v;
		n.id = id;
		n.tv = tv;
		n.cv = std::min(v, tv);
		n.v = v - n.cv;

		if (!~head) {
			n.pre = n.nxt = n.n_id;
			head = n.n_id;
		}
		else {
			Node& nxt = nodes[head];
			Node& pre = nodes[nxt.pre];
			nxt.pre = pre.nxt = n.n_id;
			n.pre = pre.n_id;
			n.nxt = nxt.n_id;
		}
	}
} infos[LEN];
std::set<int> selling, buying;

void get_selling_order(int sid, int p, int v, int tv) {
	while (buying.size() && v) {
		int pb = *(--buying.end());
		if (pb < p) break;
		if (infos[pb].SV <= v) {
			v -= infos[pb].SV;
			infos[pb].exhaust(sid, pb, 1);
			buying.erase(pb);
		}
		else {
			infos[pb].make_trade(sid, pb, v, 1);
			v = 0;
		}
	}
	if (v) selling.insert(p), infos[p].insert(sid, 2, v, tv);
}

void get_buying_order(int bid, int p, int v, int tv) {
	while (selling.size() && v) {
		int pb = *selling.begin();
		if (pb > p) break;
		if (infos[pb].SV <= v) {
			v -= infos[pb].SV;
			infos[pb].exhaust(bid, pb, 0);
			selling.erase(pb);
		}
		else {
			infos[pb].make_trade(bid, pb, v, 0);
			v = 0;
		}
	}
	if (v) buying.insert(p), infos[p].insert(bid, 1, v, tv);
}

int main() {
#ifdef DEBUG_PRINT
	freopen("input.txt", "r", stdin);
#else
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, id, t, p, v, tv; i < N; ++i) {
		std::cin >> id >> t >> p >> v >> tv;
		int nt = NT;
		if (t == SELL) get_selling_order(id, p, v, tv);
		if (t == BUY) get_buying_order(id, p, v, tv);
		std::sort(trades + nt, trades + NT);
	}

	for (int i = 0; i < NT; ++i)
		std::cout << trades[i].bid << ' ' << trades[i].sid << ' ' << trades[i].p << ' ' << trades[i].v << '\n';
	std::cout << '\n';

	for (int p = 1; p < LEN; ++p) {
		if (~infos[p].head) {
			int cur = infos[p].head;
			do {
				Node& n = nodes[cur];

				std::cout << n.id << ' ' << infos[p].type << ' ' << p << ' ' <<
					n.cv + n.v << ' ' << n.tv << ' ' << n.cv << '\n';

				cur = n.nxt;
			} while (cur != infos[p].head);
		}
	}
}