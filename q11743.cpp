#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

typedef long long ll;
const int LEN = 100'001;

struct Node {
	int pre, nxt;
	int id;
	int v, cv, tv;
} nodes[LEN];

int NT;
struct Trade {
	int bid, sid, p, v;
	bool operator<(const Trade& r) const { return bid == r.bid ? sid < r.sid : bid < r.bid; }
} trades[LEN];

struct PriceInfo {
	int head;
	ll sum;
};
std::map<int, PriceInfo> selling, buying;
std::map<int, std::set<int>> cycle_s[LEN], cycle_b[LEN];

void exhaust(int head, int id, int is_sell) {

}

void get_selling_order(int sid, int p, int v, int tv) {
	while (buying.size()) {
		auto largest = (buying.end()--);
		int pb = largest->first;
		PriceInfo info = largest->second;
		if (pb < p) break;
		if (info.sum <= v) {
			v -= info.sum;
			exhaust(info.head, sid, 1);
			selling.erase(pb);
		}
		else {

		}
	}
	if (v) {

	}
}

void get_buying_order(int bid, int p, int v, int tv) {

}

int main() {

}