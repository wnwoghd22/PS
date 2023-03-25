#include <iostream>
#include <algorithm>

typedef unsigned long long ll;
const int BELL = 21'147;
const int INF = 1e9;

int N, M;
int A[9][9];
int dp[9][9][BELL];

struct Profile {
	int connection[9];
	int idx = 0;

	Profile& operator>>=(const int& i) { idx = (idx + i) % M; return *this; }
	int& operator[](const int i) { return connection[(idx + i) % M]; }
	bool connected() {
		for (int i = 0; i < M - 1; ++i)
			if (connection[i] == connection[M - 1])
				return true;
		return false;
	}
};

int order;
class HashMap {
	struct Node {
		int key;
		int val[9];
		Node* next;
		Node(const Profile& p) : key(order++), next(0) { for (int i = 0; i < 9; ++i) val[i] = p.connection[i]; }
		bool operator==(const Profile& p) const {
			for (int i = 0; i < 9; ++i)
				if (val[i] != p.connection[i])
					return false;
			return true;
		}
	} *bucket[BELL];

	int djb2(const int s[]) const {
		ll key = 5381;
		for (int i = 0; i < M; ++i) key = ((key << 5) + key + s[i]) % BELL;
		return key;
	}
public:
	HashMap() { for (int i = 0; i < BELL; ++i) bucket[i] = 0; }
	int operator[](const Profile& p) {
		int hash = djb2(p.connection);
		if (!bucket[hash]) bucket[hash] = new Node(p);
		Node* cur = bucket[hash];
		while (true) {
			if (*cur == p) return cur->key;
			if (!cur->next) break;
			cur = cur->next;
		}
		cur->next = new Node(p);
		return cur->next->key;
	}
} map;

// ???
int f(int i, int j, Profile p) {
	if (i >= N) return -INF;
	int& ref = dp[i][j][map[p]];
	if (ref != -INF) return ref;
	ref = A[i][j];
	int con_idx = -1;
	if (!p.connected()) { // forced to select
		if (j && p.connection[0]) { // merge

		}
		else {

		}
	}
	else {

	}
	return ref;
}

int main() {
	std::cin >> N >> M;
}