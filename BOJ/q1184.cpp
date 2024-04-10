#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;
const int BUCKET_LEN = 2500;

class HashMap {
	struct Node {
		int next;
		int val;
		ll cnt;
		Node() : next(-1), val(0), cnt(1) {}
	} nodes[BUCKET_LEN];
	int size;
	int bucket[BUCKET_LEN];
	int hash(int v) const { return (5381 + v + BUCKET_LEN * BUCKET_LEN) % BUCKET_LEN; }
public:
	void clear() {
		size = 0;
		for (int i = 0; i < BUCKET_LEN; ++i)
			nodes[i] = Node(), bucket[i] = -1;
	}
	HashMap() { clear(); }
	void insert(int v) {
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
	ll operator[](int v) const {
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

int N, A[51][51], S[51][51];

int main() {
	freopen("input.txt", "r", stdin);
	ll result = 0;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			std::cin >> A[i][j];
			S[i][j] = A[i][j] + S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
		}
	}
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < N; ++j) {
			map.clear();
			for (int k = 0; k < i; ++k) {
				for (int l = 0; l < j; ++l) {
					int s = S[i][j] - S[k][j] - S[i][l] + S[k][l];
					map.insert(s);
				}
			}
			for (int k = i + 1; k <= N; ++k) {
				for (int l = j + 1; l <= N; ++l) {
					int s = S[k][l] - S[i][l] - S[k][j] + S[i][j];
					// result += map.find(s);
					result += map[s];
				}
			}

			map.clear();
			for (int k = 0; k < i; ++k) {
				for (int l = j + 1; l <= N; ++l) {
					int s = S[i][l] - S[i][j] - S[k][l] + S[k][j];
					map.insert(s);
				}
			}
			for (int k = i + 1; k <= N; ++k) {
				for (int l = 0; l < j; ++l) {
					int s = S[k][j] - S[i][j] - S[k][l] + S[i][l];
					result += map[s];
				}
			}
		}
	}
	std::cout << result;
}