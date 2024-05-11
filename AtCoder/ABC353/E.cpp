#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 5e5;
std::string S[LEN];

int N;
int nodes = 1;
struct Node {
	std::map<char, int> next;
	int cnt = 0;
} trie[LEN];

void push(const std::string& s, int i = 0, int cur = 0) {
	trie[cur].cnt++;
	if (i == s.length()) return;
	if (trie[cur].next.find(s[i]) == trie[cur].next.end()) {
		trie[cur].next[s[i]] = nodes++;
	}
	int nxt = trie[cur].next[s[i]];
	push(s, i + 1, nxt);
}

ll dfs(const std::string& s, int i = 0, int cur = 0) {
	ll ret = trie[cur].cnt; 
	if (i == s.length()) return ret;
	if (trie[cur].next.find(s[i]) == trie[cur].next.end()) {
		return ret;
	}
	int nxt = trie[cur].next[s[i]];
	return ret + dfs(s, i + 1, nxt);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	ll ret = 0;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		// std::cout << i << ' ' << dfs(S[i]) - i << '\n';
		ret += dfs(S[i]) - i;
		push(S[i]);
	}
	std::cout << ret;
}