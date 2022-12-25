#include <iostream>
#include <algorithm>
#include <queue>

char s[10001];

class Trie {
private:
	struct Node {
	public:
		Node* go[26];
		Node* fail;
		bool output;
		Node() : fail(0), output(0) {
			std::fill(go, go + 26, nullptr);
		}
		~Node() { for (Node* n : go) if (n) delete n; }
		void insert(const char* key) {
			if (*key == '\0') {
				output = true;
				return;
			}
			int next = *key - 'a';
			if (!go[next]) go[next] = new Node;
			go[next]->insert(key + 1);
		}
	};
	Node* root;
public:
	Trie() { root = new Node; }
	void insert(const char* key) { root->insert(key); }
	void make_fsm() {
		std::queue<Node*> Q;
		root->fail = root;
		Q.push(root);
		while (!Q.empty()) {
			Node* current = Q.front(); Q.pop();

			for (int i = 0; i < 26; ++i) {
				Node* next = current->go[i];
				if (!next) continue;

				if (current == root) next->fail = root;
				else {
					Node* dest = current->fail;
					while (dest != root && !dest->go[i]) dest = dest->fail;
					if (dest->go[i]) dest = dest->go[i];
					next->fail = dest;
				}
				if (next->fail->output) next->output = true;

				Q.push(next);
			}
		}
	}
	bool aho_corasick(const char* s) {
		bool result = false;
		Node* current = root;
		for (int i = 0; s[i]; ++i) {
			int next = s[i] - 'a';
			while (current != root && !current->go[next]) current = current->fail;
			if (current->go[next]) current = current->go[next];
			if (current->output) return true;
		}
		return false;
	}
};

int main() {
	Trie t;
	int N, Q;
	std::cin >> N;
	while (N--) {
		std::cin >> s;
		t.insert(s);
	}
	t.make_fsm();

	std::cin >> Q;
	while (Q--) {
		std::cin >> s;
		std::cout << (t.aho_corasick(s) ? "YES\n" : "NO\n");
	}
}