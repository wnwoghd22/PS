#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;
const int BUCKET_LEN = 10'007;

class HashMap {
	struct Node {
		Node* next;
		Node(int v) : val(v), cnt(1), next(0) {};
		int val;
		ll cnt;
	} *bucket[BUCKET_LEN];
	int hash(int v) const { return (v + BUCKET_LEN * 250) % BUCKET_LEN; }
public:
	HashMap() { for (int i = 0; i < BUCKET_LEN; ++i) bucket[i] = 0; }
	void clear() {
		for (int i = 0; i < BUCKET_LEN; ++i) {
			Node* cur = bucket[i], *next;
			while (cur) {
				next = cur->next;
				delete cur;
				cur = next;
			}
			bucket[i] = 0;
		}
	}
	void insert(int v) {
		int key = hash(v);
		if (!bucket[key]) bucket[key] = new Node(v);
		else {
			Node* cur = bucket[key], * next;
			while (true) {
				if (cur->val == v) {
					cur->cnt++;
					return;
				}
				if (!cur->next) break;
				cur = cur->next;
			}
			cur->next = new Node(v);
		}
	}
	int find(int v) {
		int key = hash(v);
		Node* cur = bucket[key];
		while (cur) {
			if (cur->val == v) { return cur->cnt; }
			cur = cur->next;
		}
		return 0;
	}
	ll operator[](int v) const {
		int key = hash(v);
		Node* cur = bucket[key];
		while (cur) {
			if (cur->val == v) { return cur->cnt; }
			cur = cur->next;
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
					result += map.find(s);
				}
			}
		}
	}
	std::cout << result;
}