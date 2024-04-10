#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 3001;
const int ALPHABET = 26;
const ll MOD = 1e9 + 7;

char s[LEN][LEN];
int N, s_len[LEN];

/// <summary>
/// ref: https://m.blog.naver.com/namhong2001/221463525400
/// </summary>
class Trie { // radix trie
	struct Node {
		Node* go[ALPHABET];
		int output, idx, match_count;
		Node() : output(0), idx(-1), match_count(0) { for (int i = 0; i < ALPHABET; ++i) go[i] = 0; }
		~Node() { for (int i = 0; i < ALPHABET; ++i) if (go[i]) delete go[i]; }
		void insert(int id, int pos) {
			if (s_len[id] == pos) {
				++output;
				return;
			}
			int next = s[id][pos] - 'a';
			if (!go[next]) {
				Node* n = new Node;
				n->idx = id;
				n->match_count = s_len[id] - pos;
				go[next] = n;
			}
			else {
				int i, n_id = go[next]->idx;
				bool full_match = true;
				for (i = 0; i < go[next]->match_count; ++i) {
					if (s_len[id] == pos + i || s[id][pos + i] != s[n_id][pos + i]) {
						full_match = false;
						break;
					}
				}
				if (!full_match) {
					Node* n = new Node;
					n->idx = id;
					n->match_count = i;
					go[next]->match_count -= i;
					int branch = s[n_id][pos + i] - 'a';
					n->go[branch] = go[next];
					go[next] = n;
				}
			}
			go[next]->insert(id, pos + go[next]->match_count);
		}
		ll dfs() {
			ll result = 0;
			for (int i = 0; i < ALPHABET; ++i) {
				if (go[i]) {
					result += go[i]->dfs();
					output += go[i]->output;
				}
			}
			// std::cout << result << ' ' << output << '\n';
			return result + output;
		}
	} *root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(int id) { root->insert(id, 0); }
	ll dfs() { return root->dfs(); }
};

int main() {
	freopen("input.txt", "r", stdin);
	std::cout << std::fixed;
	std::cout.precision(2);
	while (std::cin >> N) {
		Trie trie;
		for (int i = 0; i < N; ++i) {
			std::cin >> s[i];
			s_len[i] = strlen(s[i]);
			trie.insert(i);
		}
		ll count = trie.dfs() - N;
		// std::cout << count << '\n';
		std::cout << (double)count / N << '\n';
	}
}