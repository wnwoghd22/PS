#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

class Trie {
	struct Node {
		bool output;
		std::map<char, Node*> child;
		Node() : output(0) {}
		~Node() { for (auto [c, n] : child) delete n; }
		void insert(const std::string& s, int i) {
			if (i == s.length()) {
				output = true;
				return;
			}
			char next = s[i];
			if (child.find(next) == child.end()) child[next] = new Node;
			child[next]->insert(s, i + 1);
		}
		void find(const std::string& s, int i, bool* flag) {
			if (output) { flag[i] = true; }
			if (i == s.length()) return;
			char next = s[i];
			if (child.find(next) != child.end())
				child[next]->find(s, i + 1, flag);
		}
	}* root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(const std::string& s) { root->insert(s, 0); }
	void find(const std::string& s, bool* flag) { root->find(s, 0, flag); }
};

int C, N, Q;
bool flagC[2001], flagN[2001];

int main() {
	freopen("input.txt", "r", stdin);
	std::string s;
	Trie color, nick;
	std::cin >> C >> N;
	while (C--) {
		std::cin >> s;
		color.insert(s);
	}
	while (N--) {
		std::cin >> s;
		std::reverse(s.begin(), s.end());
		nick.insert(s);
	}
	std::cin >> Q;
	while (Q--) {
		memset(flagC, 0, sizeof flagC);
		memset(flagN, 0, sizeof flagN);
		std::cin >> s;
		color.find(s, flagC);
		std::reverse(s.begin(), s.end());
		nick.find(s, flagN);
		bool flag = false;
		for (int i = 1; i < s.length(); ++i) {
			if (flagC[i] && flagN[s.length() - i]) {
				flag = true;
				break;
			}
		}
		std::cout << (flag ? "Yes\n" : "No\n");
	}
}
