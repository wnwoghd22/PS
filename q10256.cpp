#include <iostream>
#include <algorithm>
#include <queue>

char marker[101];
char s[10001];

class Trie {
private:
	static int GATACA(char c) {
		switch (c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		}
	}
	struct Node {
	public:
		Node* go[4];
		Node* fail;
		int output;
		Node() : fail(0), output(0) {
			std::fill(go, go + 4, nullptr);
		}
		~Node() { for (Node* n : go) if (n) delete n; }
		void insert(const char* key) {
			if (*key == '\0') {
				output = 1;
				return;
			}
			int next = GATACA(*key);
			if (!go[next]) go[next] = new Node;
			go[next]->insert(key + 1);
		}
	};
	Node* root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(const char* key) { root->insert(key); }
	void make_fsm() {
		std::queue<Node*> Q;
		root->fail = root;
		Q.push(root);
		while (!Q.empty()) {
			Node* current = Q.front(); Q.pop();

			for (int i = 0; i < 4; ++i) {
				Node* next = current->go[i];
				if (!next) continue;

				if (current == root) next->fail = root;
				else {
					Node* dest = current->fail;
					while (dest != root && !dest->go[i]) dest = dest->fail;
					if (dest->go[i]) dest = dest->go[i];
					next->fail = dest;
				}
				if (next->fail->output) next->output += next->fail->output;

				Q.push(next);
			}
		}
	}
	int aho_corasick(const char* s) {
		int result = 0;
		Node* current = root;
		for (int i = 0; s[i]; ++i) {
			int next = GATACA(s[i]);
			while (current != root && !current->go[next]) current = current->fail;
			if (current->go[next]) current = current->go[next];
			result += current->output;
		}
		return result;
	}
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	int T;
	std::cin >> T;
	while (T--) {
		Trie t;
		int N, M;
		std::cin >> N >> M;
		std::cin >> s >> marker;
		t.insert(marker);
		for (int i = 0; i < M; ++i) {
			for (int j = i + 1; j <= M; ++j) {
				std::reverse(marker + i, marker + j);
				t.insert(marker);
				std::reverse(marker + i, marker + j);
			}
		}
		t.make_fsm();
		std::cout << t.aho_corasick(s) << '\n';
	}
}