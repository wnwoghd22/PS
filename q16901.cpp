#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 200'000;

int size = 1;
struct Node {
	int l, r;
	ll w;
	Node() : l(-1), r(-1), w(-1) {}
	ll get_min(ll, int);
	void insert(ll, int);
	ll dfs();
} trie[LEN * 30];

ll Node::get_min(ll a, int d) {
	if (!~d) return 0;
	if (a & 1 << d) {
		if (~r) return trie[r].get_min(a, d - 1);
		else return trie[l].get_min(a, d - 1) + (1 << d);
	}
	else {
		if (~l) return trie[l].get_min(a, d - 1);
		else return trie[r].get_min(a, d - 1) + (1 << d);
	}
}
void Node::insert(ll a, int d) {
	if (!~d) return;
	if (a & 1 << d) {
		// std::cout << a << ' ' << d << ' ';
		if (~l) {
			ll min = trie[l].get_min(a, d - 1) + (1 << d);
			if (!~w || min < w) w = min;
		}
		// std::cout << w << '\n';
		trie[~r ? r : (r = size++)].insert(a, d - 1);
	}
	else trie[~l ? l : (l = size++)].insert(a, d - 1);
}
ll Node::dfs() {
	ll result = (!~l || !~r) ? 0 : w;
	if (~l) result += trie[l].dfs();
	if (~r) result += trie[r].dfs();
	return result;
}

int N, A[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	for (int i = 0; i < N; ++i)
		trie[0].insert(A[i], 30);
	// std::cout << size << '\n';
	std::cout << trie[0].dfs();
}