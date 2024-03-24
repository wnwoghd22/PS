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

struct PriceInfo {
	int head;
	ll SV, STV;
	std::map<int, ll> diffs;
	std::map<int, ll> TVs;

	void exhaust(int id, int p, int is_sell) {
		Node n;
		int bid, sid;
		(is_sell ? sid : bid) = id;
		int cur = head;
		do {
			n = nodes[cur];
			(is_sell ? bid : sid) = n.id;
			trades[NT++] = { bid, sid, p, n.v + n.cv };
			cur = n.nxt;
		} while (cur != head);

		SV = STV = 0;
		head = -1;
		diffs.clear();
		TVs.clear();
	}
	void make_trade(int id, int p, int v, int is_sell) {
		ll cycle = 0;
		int bid, sid;
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
			if (!v) break;

			cur = n.nxt;
		} while (cur != head);

		if (cur != head) { // no cycles
			int now = head;
			do {
				Node& n = nodes[now];

				if (n.cv == 0) {
					int term = n.v / n.tv; // how many cycles remain?
					n.cv = std::min(n.v, n.tv);
					n.v -= n.cv;
					diffs[term] -= n.tv - n.cv % n.tv;
					TVs[term] -= n.tv;
					if (diffs[term] == 0) diffs.erase(term);
					if (TVs[term] == 0) TVs.erase(term);
					if (n.v) {
						if (diffs.find(term - 1) == diffs.end()) diffs[term - 1] = 0;
						if (TVs.find(term - 1) == TVs.end()) TVs[term - 1] = 0;
						diffs[term - 1] += n.tv - n.cv % n.tv;
						TVs[term - 1] += n.tv;
					}
					else STV -= n.tv;
					if (n.cv == 0 && n.v == 0) { // no volume
						Node& pre = nodes[n.pre];
						Node& nxt = nodes[n.nxt];
						pre.nxt = n.nxt;
						nxt.pre = n.pre;
					}
				}

				now = n.nxt;
			} while (now != cur);
			head = nodes[cur].nxt;
		}
		else if (nodes[head].cv == 0) { // cycle detected -> sweep
			for (const auto& iter : TVs) {
				int terms = iter.first - cycle;
				
				int cycles = v / STV;
				if (cycles <= terms) {
					cycle += cycles;
					v -= STV * cycle;
					break;
				}
				v -= STV * terms;
				ll SCV = STV - diffs[terms];
				if (v >= SCV) cycle++, v -= SCV;
				else break;

				STV -= iter.second;
			}

			diffs.clear();
			TVs.clear();
			STV = 0;

			int now = head;
			head = -1;
			do {
				Node& n = nodes[now];



				now = n.nxt;
			} while (now != head);

		}

		for (const auto& iter : traded) {
			(is_sell ? bid : sid) = iter.first;
			int volume = iter.second;
			trades[NT++] = { bid, sid, p, volume };
		}
	}
	void insert(int id, int v, int tv) {

	}
} sells[LEN], buys[LEN];
std::set<int> selling, buying;
ll SV_s[LEN * 10], SV_b[LEN * 10];

void get_selling_order(int sid, int p, int v, int tv) {
	while (buying.size() && v) {
		int pb = *(buying.end()--);
		if (pb < p) break;
		if (buys[pb].SV <= v) {
			v -= buys[pb].SV;
			buys[pb].exhaust(sid, pb, 1);
			buying.erase(pb);
		}
		else {
			buys[pb].make_trade(sid, pb, v, 1);
			v = 0;
		}
	}
	if (v) sells[p].insert(sid, v, tv);
}

void get_buying_order(int bid, int p, int v, int tv) {
	while (selling.size() && v) {
		int pb = *selling.begin();
		if (pb > p) break;
		if (sells[pb].SV <= v) {
			v -= sells[pb].SV;
			sells[pb].exhaust(bid, pb, 0);
			selling.erase(pb);
		}
		else {
			sells[pb].make_trade(bid, pb, v, 0);
			v = 0;
		}
	}
	if (v) buys[p].insert(bid, v, tv);
}

int main() {

}