#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

char tile[5'001];
char street[300'001];
int mark[300'001], chk[300'001];
int N, M;

class Trie {
private:
	struct Node {
	public:
		std::vector<std::pair<char, Node*>> go;
		Node* fail;
		int len;
		Node() : fail(0), len(0) { }
		~Node() { for (auto [k, n] : go) delete n; }
		void insert(const char* key, const int& len) {
			if (*key == '\0') {
				this->len = std::max(this->len, len);
				return;
			}
			int next = *key;
			for (auto [c, n] : go) {
				if (c == next) return n->insert(key + 1, len);
			}
			go.push_back({ next, new Node });
			go.back().second->insert(key + 1, len);
		}
	};
	Node* root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(const char* key) { root->insert(key, strlen(key)); }
	void make_fsm() {
		std::queue<Node*> Q;
		root->fail = root;
		Q.push(root);
		while (!Q.empty()) {
			Node* current = Q.front(); Q.pop();

			for (auto [i, next] : current->go) {
				if (!next) continue;

				if (current == root) next->fail = root;
				else {
					Node* dest = current->fail;
					while (dest != root) {
						bool flag = true;
						for (auto [j, n] : dest->go) {
							if (i == j) {
								flag = false;
								break;
							}
						}
						if (!flag) break;
						dest = dest->fail;
					}
					for (auto [j, n] : dest->go) {
						if (j == i) {
							dest = n;
							break;
						}
					}
					next->fail = dest;
				}
				if (next->fail->len) {
					next->len = std::max(next->len, next->fail->len);
				}

				Q.push(next);
			}
		}
	}
	int aho_corasick_masking(const char* s) {
		Node* current = root;
		for (int i = 0, j = -1; s[i]; ++i) {
			int next = s[i];
			while (current != root) {
				bool flag = true;
				for (auto [k, n] : current->go) {
					if (k == next) {
						flag = false;
						break;
					}
				}
				if (!flag) break;
				current = current->fail;
			}
			for (auto [k, n] : current->go) {
				if (k == next) {
					current = n;
					break;
				}
			}
			if (current->len) {
				// int masking = std::min(i - j, current->len);
				// result -= masking;
				// j = i;
				mark[i] = std::max(mark[i], current->len);
			}
		}
		int result = 0;
		for (int i = N - 1; i >= 0; --i) {
			int check = mark[i];
			if (check == 0 && chk[i] == 0) result++;
			while (chk[i - check + 1] == 0 && i - check + 1 <= i) {
				chk[i - check + 1] = 1;
				check--;
			}
		}

		return result;
	}
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	Trie t;
	std::cin >> N;
	std::cin >> street;
	std::cin >> M;
	while (M--) {
		std::cin >> tile;
		t.insert(tile);
	}
	t.make_fsm();
	std::cout << t.aho_corasick_masking(street);
}