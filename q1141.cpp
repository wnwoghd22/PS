#include <iostream>
#include <map>

typedef long long int ll;
class Trie {
private:
	struct Node {
	public:
		std::map<char, Node*> go;
		int output;
		Node() : output(0) { }
		~Node() { for (auto [k, n] : go) delete n; }
		void insert(std::string s, int i) {
			if (i == s.length()) {
				output += 1;
				return;
			}
			char next = s[i];
			if (go.find(next) == go.end()) go[next] = new Node;
			go[next]->insert(s, i + 1);
		}
		ll dfs() const {
			bool leaf = 1, int cnt = 0;
			for (const auto& [k, n] : go) cnt += n->dfs(), leaf = 0;
			return leaf + cnt;
		}
	};
	Node* root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(std::string s) { root->insert(s, 0); }
	ll get_count() const { return root->dfs(); }
};

int main() {
	Trie t;
	int N;
	std::string s;
	std::cin >> N;
	while (N--) {
		std::cin >> s;
		t.insert(s);
	}
	std::cout << t.get_count();
}