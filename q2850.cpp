#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;
const int MAX = 500'001;
const int MOD = 1e4 + 7;

int N, M;
char A[10][11];
int dp[10][10][MAX];

struct Profile {
	int connection[10], r;
	int idx = 0;
	Profile() : idx(0) { for (int i = 0; i < 10; ++i) connection[i] = 0; r = 0; }
	Profile(const Profile& p) : idx(p.idx) { for (int i = 0; i < 10; ++i) connection[i] = p.connection[i]; r = p.r; }
	int& operator[](const int i) { return connection[(idx - i + M) % M]; }
	int operator[](const int i) const { return connection[(idx - i + M) % M]; }
	Profile operator<<(const int& i) const { Profile p(*this); p.idx = (idx + i) % M; p[0] = 0; p.r = 0; return p; }
	Profile& operator=(const Profile& p) {
		if (this != &p) {
			idx = p.idx;
			r = p.r;
			for (int i = 0; i < 10; ++i)
				connection[i] = p.connection[i];
		}
		return *this;
	}
	Profile normalize() {
		static int temp[10];
		Profile p(*this);
		int i, k;
		for (k = 0; k < 10; ++k) temp[k] = 0;
		for (k = 0, i = 1; k < M; ++k) {
			int c = (*this)[k];
			if (!c) continue;
			if (!temp[c]) temp[c] = i++;
			p[k] = temp[c];
		}
		if (r) {
			if (!temp[r]) temp[r] = i++;
			p.r = temp[r];
		}
		return p;
	}
	bool valid() const {
		if (!(*this)[0]) return false;
		for (int i = 1; i < M; ++i) if ((*this)[i]) return false;
		if (r) return false;
		return true;
	}
	Profile merge() {
		Profile p = *this << 1;

		int cur = (*this)[M - 1];
		for (int i = 0; i < M; ++i) {
			if (p[i] == cur)
				p[i] = r;
		}

		return p.normalize();
	}
};

int order;
class HashMap {
	struct Node {
		int key;
		int val[10], r;
		Node* next;
		Node(const Profile& p) : key(order++), next(0) { for (int i = 0; i < M; ++i) val[i] = p[i]; r = p.r; }
		bool operator==(const Profile& p) const {
			for (int i = 0; i < M; ++i)
				if (val[i] != p[i])
					return false;
			if (r != p.r) return false;
			return true;
		}
	} *bucket[MAX];

	int djb2(const Profile& p) const {
		ll key = 5381;
		for (int i = 0; i < M; ++i)
			key = ((key << 5) + key + p[i]) % MAX;
		key = ((key << 5) + key + p.r) % MAX;
		return key;
	}
public:
	HashMap() { for (int i = 0; i < MAX; ++i) bucket[i] = 0; }
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

int f(int i, int j, Profile p) {
	std::cout << "f(" << i << ' ' << j << ")\n";
	std::cout << "profile:\n";
	std::cout << "[";
	for (int k = 0; k < M; ++k) std::cout << p[k] << ' ';
	std::cout << "] & " << p.r << '\n';
	if (i >= N) {
		std::cout << "final: " << p.valid() << '\n';
		return p.valid();
	}
	int& ref = dp[i][j][map[p]];

	if (~ref) return ref;
	ref = 0;
	
	if (!p.r && !p[M - 1]) { // empty
		Profile next = p << 1;
		ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
	}

	if (A[i][j] != '#') {
		if (p.r && !p[M - 1] && j != M - 1 && A[i][j + 1] != '#') { // l-r tile
			std::cout << "l-r\n";
			Profile next = p << 1;
			next.r = p.r;
			ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
		}
		if (p.r && p[M - 1] && p.r != p[M - 1]) { // l-u tile
			std::cout << "l-u\n";
			Profile next = p.merge();
			ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
		}
		if (!p.r && p[M - 1]) { // u-r, u-d tile
			if (j != M - 1 && A[i][j + 1] != '#') { // u-r
				std::cout << "u-r\n";
				Profile next = p << 1;
				next.r = p[M - 1];
				ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
			}
			std::cout << "u-d\n";
			Profile next = p << 1; // u-d
			next[0] = p[M - 1];
			ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
		}
		if (p.r && !p[M - 1]) { // l-d tile
			std::cout << "l-d\n";
			Profile next = p << 1;
			next[0] = p.r;
			ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
		}
		if (!p.r && !p[M - 1] && j != M - 1) { // d-r tile
			std::cout << "d-r\n";
			Profile next = p << 1;
			next[0] = next.r = 9;
			ref = (ref + f(i + (j + 1) / M, (j + 1) % M, next.normalize())) % MOD;
		}
	}
	std::cout << "-----------[" << i << ' ' << j << "]: " << ref << '\n';

	return ref;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	memset(dp, -1, sizeof dp);

	Profile p;
	p[M - 1] = 1;
	std::cout << f(0, 0, p);
	// std::cout << "\nmap size: " << order << '\n';
}