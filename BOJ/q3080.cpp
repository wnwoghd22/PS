#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 3001;
const int ALPHABET = 26;
const ll MOD = 1e9 + 7;

char s[LEN][LEN];
int N, s_len[LEN];
ll fact[LEN] = { 1, 1, };

/// <summary>
/// ref: https://m.blog.naver.com/namhong2001/221463525400
/// </summary>
class Trie { // radix trie
	struct Node {
		Node* go[ALPHABET];
		int degree, idx, match_count;
		Node() : degree(0), idx(-1), match_count(0) { for (int i = 0; i < ALPHABET; ++i) go[i] = 0; }
		~Node() { for (int i = 0; i < ALPHABET; ++i) if (go[i]) delete go[i]; }
		void insert(int id, int pos) {
			if (s_len[id] == pos) {
				++degree;
				return;
			}
			/*std::cout << idx << ' ' << match_count << ' ' << pos << ' ';
			for (int i = 0; i < match_count; ++i) {
				std::cout << s[idx][i];
			}
			std::cout << '\n';*/
			int next = s[id][pos] - 'A';
			if (!go[next]) {
				++degree;
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
					int branch = s[n_id][pos + i] - 'A';
					n->go[branch] = go[next];
					n->degree = 1;
					go[next] = n;
				}
			}
			go[next]->insert(id, pos + go[next]->match_count);
		}
		ll dfs() {
			// std::cout << idx << ' ' << match_count << ' ' << degree << '\n';
			ll result = fact[degree];
			for (int i = 0; i < ALPHABET; ++i) {
				if (go[i]) {
					result *= go[i]->dfs();
					result %= MOD;
				}
			}
			return result;
		}
	} *root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(int id) { root->insert(id, 0); }
	ll dfs() { return root->dfs(); }
} trie;

int main() {
	for (int i = 2; i < 30; ++i) 
		fact[i] = fact[i - 1] * i % MOD;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> s[i];
		s_len[i] = strlen(s[i]);
		trie.insert(i);
	}
	std::cout << trie.dfs();
}