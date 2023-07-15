#include <iostream>

const int LEN = 1500;

typedef long long ll;
const int BUCKET_LEN = 1531;

struct Pos { 
	int x, y;
	Pos() : x(0), y(0) {}
	Pos(int x, int y) : x(x), y(y) {}
	bool operator==(const Pos& r) const { return x == r.x && y == r.y; }
} pos[LEN];

class HashMap {
public:
	struct Node {
		int next;
		Pos val;
		ll cnt;
		Node() : next(-1), val(), cnt(1) {}
	} nodes[BUCKET_LEN];
	int size;
	int bucket[BUCKET_LEN];
	int hash(const Pos& v) const {
		ll key = 5381;
		key += v.x;
		key = key << 5 + key;
		if (key < 0) key *= -1;
		key %= BUCKET_LEN;
		key += v.y;
		key = key << 5 + key;
		if (key < 0) key *= -1;
		key %= BUCKET_LEN;
		return key;
	}
	void clear() {
		size = 0;
		for (int i = 0; i < BUCKET_LEN; ++i)
			nodes[i] = Node(), bucket[i] = -1;
	}
	HashMap() { clear(); }
	void insert(const Pos& v) {
		int key = hash(v);
		if (!~bucket[key]) {
			nodes[size].val = v;
			bucket[key] = size++;
		}
		else {
			int cur = bucket[key];
			while (true) {
				if (nodes[cur].val == v) {
					nodes[cur].cnt++;
					return;
				}
				if (!~nodes[cur].next) break;
				cur = nodes[cur].next;
			}
			nodes[size].val = v;
			nodes[cur].next = size++;
		}
	}
	ll operator[](const Pos& v) const {
		int key = hash(v);
		if (~bucket[key]) {
			int cur = bucket[key];
			while (true) {
				if (nodes[cur].val == v) return nodes[cur].cnt;
				if (!~nodes[cur].next) break;
				cur = nodes[cur].next;
			}
		}
		return 0;
	}
} map;

int N;

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> pos[i].x >> pos[i].y;

	int sum = 0;
	for (int i = 0; i < N; ++i) {
		map.clear();
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			int x = pos[j].x - pos[i].x;
			int y = pos[j].y - pos[i].y;
			int g = gcd(abs(x), abs(y));
			x /= g, y /= g;
			map.insert({ x, y });
		}
		for (int j = 0; j < BUCKET_LEN; ++j) {
			Pos p = map.nodes[j].val;
			int c = map.nodes[j].cnt;
			if (!c) continue;

			sum += map[{ p.y, -p.x }] * c;
			sum += map[{ -p.y, p.x }] * c;
		}
	}
	std::cout << (sum >> 1);
}