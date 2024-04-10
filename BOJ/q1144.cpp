#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;
const int BELL = 21'147;
const int INF = 1e9 + 7;

int N, M;
int A[9][9];
int dp[9][9][BELL];

struct Profile {
	int connection[9];
	int idx = 0;
	Profile() : idx(0) { for (int i = 0; i < 9; ++i) connection[i] = 0; }
	Profile(const Profile& p) : idx(p.idx) { for (int i = 0; i < 9; ++i) connection[i] = p.connection[i]; }
	int& operator[](const int i) { return connection[(idx - i + M) % M]; }
	int operator[](const int i) const { return connection[(idx - i + M) % M]; }
	Profile operator<<(const int& i) const { Profile p(*this); p.idx = (idx + i) % M; p[0] = 0; return p; }
	Profile& operator<<=(const int& i) { idx = (idx + i) % M; connection[idx] = 0; return *this; }
	Profile& operator=(const Profile& p) {
		if (this != &p) {
			idx = p.idx;
			for (int i = 0; i < 9; ++i)
				connection[i] = p.connection[i];
		}
		return *this;
	}
	bool connected(int i) {
		if (!(*this)[i]) return true;
		for (int k = 0; k < M; ++k) {
			if (k == i) continue;
			if ((*this)[k] == (*this)[i]) return true;
		}
		return false;
	}
	Profile normalize() {
		static int temp[6];
		Profile p(*this);
		for (int k = 0; k < 6; ++k) temp[k] = 0;
		for (int k = 0, i = 1; k < M; ++k) {
			int c = (*this)[k];
			if (!c) continue;
			if (!temp[c]) temp[c] = i++;
			p[k] = temp[c];
		}
		return p;
	}
	int count() const {
		static bool temp[6];
		int i = 0;
		for (int k = 0; k < 6; ++k) temp[k] = 0;
		for (int k = 0; k < M; ++k) {
			int c = connection[k];
			if (!c) continue;
			if (!temp[c]) temp[c] = 1, ++i;
		}
		return i;
	}
	Profile merge() {
		Profile p = *this << 1;
		if (idx) { // y > 0. need to check left
			if (!(*this)[0] && !(*this)[M - 1]) p[0] = 5; // left = 0, top = 0. new connection
			else if (!(*this)[0]) p[0] = (*this)[M - 1]; // left = 0, top != 0. merge top
			else if (!(*this)[M - 1] || (*this)[0] == (*this)[M - 1]) p[0] = (*this)[0]; // top = 0 or left = top. merge left
			else { // left != top, merge left-top
				p[0] = (*this)[0];
				for (int i = 0; i < M; ++i) // p[top~] merge to p[0]
					if (p[i] == (*this)[M - 1])
						p[i] = (*this)[0];
			}
		}
		else p[0] = (*this)[M - 1] ? (*this)[M - 1] : 5;
		
		return p.normalize();
	}
};

int order;
class HashMap {
	struct Node {
		int key;
		int val[9];
		Node* next;
		Node(const Profile& p) : key(order++), next(0) { for (int i = 0; i < M; ++i) val[i] = p[i]; }
		bool operator==(const Profile& p) const {
			for (int i = 0; i < M; ++i)
				if (val[i] != p[i])
					return false;
			return true;
		}
	} *bucket[BELL];

	int djb2(const Profile& p) const {
		ll key = 5381;
		for (int i = 0; i < M; ++i)
			key = ((key << 5) + key + p[i]) % BELL;
		return key;
	}
public:
	HashMap() { for (int i = 0; i < BELL; ++i) bucket[i] = 0; }
	int operator[](const Profile& p) {
		int hash = djb2(p);
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
	if (i >= N) return p.count() <= 1 ? 0 : INF - 1;
	int& ref = dp[i][j][map[p]];
	if (ref != INF) return ref;
	ref -= 1;

	if (p.connected(M - 1)) ref = std::min(ref, f(i + (j + 1) / M, (j + 1) % M, p << 1));
	ref = std::min(ref, f(i + (j + 1) / M, (j + 1) % M, p.merge()) + A[i][j]);
	if (p.count() <= 1) ref = std::min(ref, 0);

	return ref;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> A[i][j];
			for (int k = 0; k < BELL; ++k)
				dp[i][j][k] = INF;
		}
	}
	std::cout << f(0, 0, Profile());
	std::cout << "\nmap size: " << order << '\n';
}