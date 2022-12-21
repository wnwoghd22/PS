#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

char tile[5'001];
char street[3'00'001];

class Trie {
private:
	struct Node {
	public:
		std::map<char, Node*> go;
		Node* fail;
		int output, len;
		Node() : fail(0), output(0), len(0) { }
		~Node() { for (auto [k, n] : go) delete n; }
		void insert(const char* key, const int& len) {
			if (*key == '\0') {
				output = 1;
				this->len = len;
				return;
			}
			int next = *key;
			if (go.find(next) == go.end()) go[next] = new Node;
			go[next]->insert(key + 1, len);
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
					while (dest != root && !dest->go[i]) dest = dest->fail;
					if (dest->go[i]) dest = dest->go[i];
					next->fail = dest;
				}
				if (next->fail->output) {
					next->output += next->fail->output;
					next->len = std::max(next->len, next->fail->len);
				}

				Q.push(next);
			}
		}
	}
	int aho_corasick_masking(const char* s) {
		int result = strlen(s);
		Node* current = root;
		for (int i = 0, j = -1; s[i]; ++i) {
			int next = s[i];
			while (current != root && !current->go[next]) current = current->fail;
			if (current->go[next]) current = current->go[next];
			if (current->output) {
				std::cout << i << ' ' << current->len << ' ' << j << '\n';
				int masking = std::min(i - j, current->len);
				std::cout << masking << '\n';
				result -= masking;
				j = i;
			}
		}
		return result;
	}
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	Trie t;
	int N, M;
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