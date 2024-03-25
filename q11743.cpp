#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

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

struct E {
	int v, tv;
	bool operator<(const E& r) const { return v / tv < r.v / r.tv; }
} orders[LEN];
int terms[LEN];
ll TVs[LEN];
ll diffs[LEN];

struct PriceInfo {
	int head = -1, type = -1;
	ll SV;

	void exhaust(int id, int p, int is_sell) {
		Node n;
		int bid, sid;
		(is_sell ? sid : bid) = id;
		int cur = head;
		do {
			n = nodes[cur];
			(is_sell ? bid : sid) = n.id;
			insert_trade(bid, sid, p, n.v + n.cv);
			cur = n.nxt;
		} while (cur != head);

		SV = 0;
		head = type = -1;
	}
	void make_trade(int id, int p, int v, int is_sell) {
		int bid, sid;
		int last_ordered = -1, refilled = 0;
		std::map<int, int> traded;

		(is_sell ? sid : bid) = id;
		SV -= v;

		// exhaust cv
		int cur = head;
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
			cur = head;
			while (1) {
				Node& n = nodes[cur];

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
				cur = n.nxt;
			}
		}
		else { // cycle detected -> sweep
			ll cycle = 0, STV = 0;
			int P = 0, Q = 0;
			cur = head;
			do {
				Node& n = nodes[cur];
				orders[P++] = { n.v, n.tv };
				cur = n.nxt;
			} while (cur != head);
			std::sort(orders, orders + P);

			terms[0] = orders[0].v / orders[0].tv;
			TVs[0] = orders[0].tv;
			diffs[0] = orders[0].tv - orders[0].v % orders[0].tv;
			STV += orders[0].tv;

			for (int i = 1, term, diff; i < P; ++i) {
				if (!orders[i].v) continue;
				STV += orders[i].tv;
				term = orders[i].v / orders[i].tv;
				diff = orders[i].tv - orders[i].v % orders[i].tv;
				if (term != terms[Q]) {
					++Q;
					terms[Q] = term;
					TVs[Q] = orders[i].tv;
					diffs[Q] = diff;
				}
				else {
					TVs[Q] += orders[i].tv;
					diffs[Q] += diff;
				}
			}

			for (int i = 0; i <= Q; ++i) {
				int term = terms[i] - cycle;
				if (term) {
					int cycles = v / STV;
					if (cycles < term) {
						cycle += cycles;
						v -= STV * cycles;
						if (!v) last_ordered = nodes[nodes[head].pre].n_id;
						break;
					}
					v -= STV * term;
					cycle += term;

					if (!v) {
						last_ordered = nodes[nodes[head].pre].n_id;
						break;
					}
				}
				ll SCV = STV - diffs[i];
				if (v > SCV) cycle++, v -= SCV;
				else if (v <= SCV) break;
				STV -= TVs[i];
			}

			std::set<int> visited;

			cur = head;
			while (1) {
				Node& n = nodes[cur];
				if (visited.find(n.id) != visited.end()) break;
				visited.insert(n.id);

				int term = n.v / n.tv + !!(n.v % n.tv);
				if (!v && n.n_id == last_ordered && !n.cv) refilled = 1;

				if (term <= cycle) {
					traded[n.id] += n.v;
					n.v = n.cv = 0;
					Node& pre = nodes[n.pre];
					Node& nxt = nodes[n.nxt];
					pre.nxt = n.nxt;
					nxt.pre = n.pre;
				}
				else {
					n.v -= n.tv * cycle;
					traded[n.id] += n.tv * cycle;
					n.cv = std::min(n.tv, n.v);
					n.v -= n.cv;
					if (v) {
						int delta = std::min(v, n.cv);
						traded[n.id] += delta;

						v -= delta;
						n.cv -= delta;

						if (!~last_ordered && v == 0) {
							last_ordered = n.n_id;
							if (!n.cv) refilled = 1;
						}
						if (n.cv == 0) {
							n.cv = std::min(n.tv, n.v);
							n.v -= n.cv;
						}
					}
					if (!n.cv) {
						Node& pre = nodes[n.pre];
						Node& nxt = nodes[n.nxt];
						pre.nxt = n.nxt;
						nxt.pre = n.pre;
					}
				}
				cur = n.nxt;
			}
		}

		head = last_ordered;
		if (refilled) {
			head = nodes[head].nxt;
			while (nodes[head].v + nodes[head].cv == 0) head = nodes[head].nxt;
		}

		for (const auto& iter : traded) {
			(is_sell ? bid : sid) = iter.first;
			int volume = iter.second;
			insert_trade(bid, sid, p, volume);
		}
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
std::priority_queue<int> selling, buying;

void get_selling_order(int sid, int p, int v, int tv) {
	while (buying.size() && v) {
		int pb = buying.top();

		if (pb < p) break;
		if (infos[pb].SV <= v) {
			v -= infos[pb].SV;
			infos[pb].exhaust(sid, pb, 1);
			buying.pop();
		}
		else {
			infos[pb].make_trade(sid, pb, v, 1);
			v = 0;
		}
	}
	if (v) {
		if (infos[p].type != SELL) selling.push(-p);
		infos[p].insert(sid, SELL, v, tv);
	}
}

void get_buying_order(int bid, int p, int v, int tv) {
	while (selling.size() && v) {
		int pb = -selling.top();

		if (pb > p) break;
		if (infos[pb].SV <= v) {
			v -= infos[pb].SV;
			infos[pb].exhaust(bid, pb, 0);
			selling.pop();
		}
		else {
			infos[pb].make_trade(bid, pb, v, 0);
			v = 0;
		}
	}
	if (v) {
		if (infos[p].type != BUY) buying.push(p);
		infos[p].insert(bid, BUY, v, tv);
	}
}

int main() {
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