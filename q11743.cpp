#define _CRT_SECURE_NO_WARNINGS
#define DEBUG_PRINT 1
#undef DEBUG_PRINT

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
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
void insert_trade(int bid, int sid, int p, int v) {
#ifdef DEBUG_PRINT
	std::cout << "make trade: " << bid << ' ' << sid << ' ' << p << ' ' << v << '\n';
#endif
	trades[NT++] = { bid, sid, p, v };
}

struct PriceInfo {
	int head = -1, type = -1;
	ll SV, STV;
	std::map<int, ll> diffs;
	std::map<int, ll> TVs;

	void exhaust(int id, int p, int is_sell) {
#ifdef DEBUG_PRINT
		std::cout << "!EXHAUST ALL ORDER: " << p << ' ' << (is_sell ? "SELL" : "BUY") << '\n';
#endif
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

		SV = STV = 0;
		head = -1;
		diffs.clear();
		TVs.clear();
#ifdef DEBUG_PRINT
		std::cout << '\n';
#endif
	}
	void make_trade(int id, int p, int v, int is_sell) {
#ifdef DEBUG_PRINT
		std::cout << "!MAKE TRADES... : " << p << ' ' << v << ' ' << (is_sell ? "SELL" : "BUY") << '\n';
#endif
		int bid, sid;
		int last_ordered = -1;
		std::map<int, int> traded;

		(is_sell ? sid : bid) = id;
		SV -= v;

		// exhaust cv
#ifdef DEBUG_PRINT
		std::cout << "	exhaust cv\n";
#endif
		int cur = head;
		assert(~cur);
		do {
			Node& n = nodes[cur];
			int delta = std::min(v, n.cv);

#ifdef DEBUG_PRINT
			std::cout << "		id: " << n.id << ", cv: " << n.cv << ", n.v: " << n.v << ", v: " << v << ", delta : " << delta << '\n';
#endif

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
#ifdef DEBUG_PRINT
				std::cout << "	no cycle\n";
#endif
			int now = head;
			bool refilled = 0;
			while (1) {
				Node& n = nodes[now];

				if (n.cv == 0) {
#ifdef DEBUG_PRINT
					std::cout << "		refill cv: " << n.id << "\n";
#endif
					if (n.n_id == last_ordered) refilled = 1;

					int term = n.v / n.tv; // how many cycles remain?
					diffs[term] -= n.tv - n.v % n.tv;
					TVs[term] -= n.tv;
					if (diffs[term] == 0) diffs.erase(term);
					if (TVs[term] == 0) TVs.erase(term);
					n.cv = std::min(n.v, n.tv);
					n.v -= n.cv;
#ifdef DEBUG_PRINT
					std::cout << "			pop diffs: " << term << ' ' << n.tv - n.v % n.tv << "\n";
					std::cout << "			pop TV: " << term << ' ' << n.tv << "\n";
#endif
					if (n.v) {
						int term = n.v / n.tv;
						if (diffs.find(term) == diffs.end()) diffs[term] = 0;
						if (TVs.find(term) == TVs.end()) TVs[term] = 0;
						diffs[term] += n.tv - n.v % n.tv;
						TVs[term] += n.tv;
#ifdef DEBUG_PRINT
						std::cout << "			push diffs: " << term << ' ' << n.tv - n.v % n.tv << "\n";
						std::cout << "			push TV: " << term << ' ' << n.tv << "\n";
#endif
					}
					else STV -= n.tv;
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
		else { // cycle detected -> sweep
#ifdef DEBUG_PRINT
				std::cout << "	cycle detected\n";
#endif

			ll cycle = 0;

			for (const auto& iter : TVs) {
#ifdef DEBUG_PRINT
				std::cout << "		current cycle: " << cycle << '\n';
				std::cout << "		current STV: " << STV << '\n';
				std::cout << "		remains: " << v << '\n';
#endif
				int key = iter.first;
				int terms = key - cycle;
#ifdef DEBUG_PRINT
				std::cout << "		terms: " << terms << '\n';
#endif
				if (terms) {
					int cycles = v / STV;
#ifdef DEBUG_PRINT
					std::cout << "		cycles: " << cycles << '\n';
#endif
					if (cycles < terms) {
#ifdef DEBUG_PRINT
						std::cout << "			reduce cycles and break\n";
						std::cout << "			v: " << v << ", STV: " << STV << ", cycles: " << cycles << '\n';
#endif
						cycle += cycles;
						v -= STV * cycles;
						if (!v) {
							last_ordered = nodes[nodes[head].pre].n_id;
#ifdef DEBUG_PRINT
							std::cout << "				last ordered: " << last_ordered << '\n';
#endif
						}
						break;
					}
					v -= STV * terms;
					cycle += terms;
					if (!v) {
						last_ordered = nodes[nodes[head].pre].n_id;
#ifdef DEBUG_PRINT
						std::cout << "				last ordered: " << last_ordered << '\n';
#endif
						break;
					}
				}

				ll SCV = STV - diffs[key];

#ifdef DEBUG_PRINT
				std::cout << "		check diffs\n";
				std::cout << "		current diff: " << diffs[key] << '\n';
				std::cout << "		current cycle: " << cycle << '\n';
				std::cout << "		current SCV: " << SCV << '\n';
				std::cout << "		remains: " << v << '\n';
#endif

				if (v > SCV) cycle++, v -= SCV;
				else if (v <= SCV) break;

				STV -= iter.second;
			}

			diffs.clear();
			TVs.clear();
			STV = 0;

			std::set<int> visited;

#ifdef DEBUG_PRINT
			std::cout << "	sweep with cycle " << cycle << "\n";
			std::cout << "	remains: " << v << '\n';
			std::cout << "	last ordered: " << last_ordered << '\n';
#endif
			int now = head;
			bool refilled = 0;
			while (1) {
				Node& n = nodes[now];
				if (visited.find(n.id) != visited.end()) break;
				visited.insert(n.id);

				int terms = n.v / n.tv + !!(n.v % n.tv);

#ifdef DEBUG_PRINT
				std::cout << "		n id: " << n.n_id << ", id: " << n.id << ", n.v : " << n.v << ", n.tv : " << n.tv <<  ", terms : " << terms << '\n';
#endif

				if (terms <= cycle) {
#ifdef DEBUG_PRINT
					std::cout << "			erase: " << n.id << '\n';
#endif
					traded[n.id] += n.v;
					n.v = n.cv = 0;
					Node& pre = nodes[n.pre];
					Node& nxt = nodes[n.nxt];
					pre.nxt = n.nxt;
					nxt.pre = n.pre;

					if (!v && n.n_id == last_ordered && !n.cv) refilled = 1;
				}
				else {
#ifdef DEBUG_PRINT
					std::cout << "			process: " << n.id << '\n';
					std::cout << "				remains: " << v << '\n';
					std::cout << "				cycle: " << cycle << '\n';
					std::cout << "				n.v: " << n.v << '\n';
					std::cout << "				n.tv: " << n.tv << '\n';
#endif
					if (!v && n.n_id == last_ordered && !n.cv) refilled = 1;
					assert(n.tv * cycle <= n.v);
					n.v -= n.tv * cycle;
					traded[n.id] += n.tv * cycle;
					n.cv = std::min(n.tv, n.v);
					n.v -= n.cv;
#ifdef DEBUG_PRINT
					std::cout << "			after reduced\n";
					std::cout << "				n.v: " << n.v << '\n';
					std::cout << "				n.tv: " << n.tv << '\n';
					std::cout << "				n.cv: " << n.cv << '\n';
#endif

					if (v) {
#ifdef DEBUG_PRINT
						std::cout << "			check last cycle: " << n.id << '\n';
#endif
						int delta = std::min(v, n.cv);
						traded[n.id] += delta;
#ifdef DEBUG_PRINT
						std::cout << "				delta: " << delta << '\n';
#endif
						v -= delta;
						n.cv -= delta;

						if (!~last_ordered && v == 0) {
							last_ordered = n.n_id;
							if (!n.cv) refilled = 1;
#ifdef DEBUG_PRINT
							std::cout << "				last ordered: " << n.id << '\n';
#endif
						}
						if (n.cv == 0) {
							n.cv = std::min(n.tv, n.v);
							n.v -= n.cv;
							if (!n.cv) {
								Node& pre = nodes[n.pre];
								Node& nxt = nodes[n.nxt];
								pre.nxt = n.nxt;
								nxt.pre = n.pre;
							}
						}
					}
#ifdef DEBUG_PRINT
					std::cout << "			node: " << n.n_id << ' ' << n.id << ' ' << n.v << ' ' << n.tv << ' ' << n.cv << '\n';
#endif
				}

				if (n.v) {
					int term = n.v / n.tv;
					if (diffs.find(term) == diffs.end()) diffs[term] = 0;
					if (TVs.find(term) == TVs.end()) TVs[term] = 0;
					diffs[term] += n.tv - n.v % n.tv;
					TVs[term] += n.tv;
					STV += n.tv;
#ifdef DEBUG_PRINT
					std::cout << "			push diffs: " << term << ' ' << n.tv - n.v % n.tv << "\n";
					std::cout << "			push TV: " << term << ' ' << n.tv << "\n";
#endif
				}

				now = n.nxt;
			}
			assert(!v);
			assert(~last_ordered);
			head = last_ordered;
			if (refilled) {
				head = nodes[head].nxt;
				while (nodes[head].v + nodes[head].cv == 0) head = nodes[head].nxt;
			}
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

#ifdef DEBUG_PRINT
			std::cout << "	node: " << n.id << ' ' << n.v << ' ' << n.tv << ' ' << n.cv << "\n\n";
#endif

		if (n.v) {
			int term = n.v / n.tv;
			if (diffs.find(term) == diffs.end()) diffs[term] = 0;
			if (TVs.find(term) == TVs.end()) TVs[term] = 0;
			diffs[term] += n.tv - n.v % n.tv;
			TVs[term] += n.tv;
			STV += n.tv; 
#ifdef DEBUG_PRINT
			std::cout << "			push diffs: " << term << ' ' << n.tv - n.v % n.tv << "\n";
			std::cout << "			push TV: " << term << ' ' << n.tv << "\n";
#endif
		}
		
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
#ifdef DEBUG_PRINT
	std::cout << "got selling order! : " << sid << ' ' << p << "\n";
#endif

	while (buying.size() && v) {
		int pb = *(--buying.end());
#ifdef DEBUG_PRINT
		std::cout << "largest: " << pb << '\n';
#endif
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
	if (v) {
#ifdef DEBUG_PRINT
		std::cout << "insert selling order : " << sid << ' ' << p << ' ' << v << ' ' << tv << '\n';
#endif
		selling.insert(p), infos[p].insert(sid, 2, v, tv);
	}
}

void get_buying_order(int bid, int p, int v, int tv) {
#ifdef DEBUG_PRINT
	std::cout << "got buying order! : " << bid << ' ' << p << "\n";
#endif

	while (selling.size() && v) {
		int pb = *selling.begin();
#ifdef DEBUG_PRINT
		std::cout << "smallest: " << pb << '\n';
#endif
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