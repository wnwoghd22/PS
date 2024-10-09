#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

typedef long long int ll;

class Trie {
	struct Node {
		int output;
		std::map<char, Node*> child;
		Node() : output(0) {}
		~Node() { for (auto [c, n] : child) delete n; }
		void insert(const std::string& s, int i) {
			++output;
			if (i == s.length()) return;
			char next = s[i];
			if (child.find(next) == child.end()) child[next] = new Node;
			child[next]->insert(s, i + 1);
		}
		int erase(const std::string& s, int i) {
			--output;
			if (i == s.length()) return output;
			char next = s[i];
			if (child.find(next) != child.end()) {
				int r = child[next]->erase(s, i + 1);
				if (!r) {
					// std::cout << "delete: " << s << ", " << next << '\n';
					delete child[next];
					child.erase(next);
				}
			}
			return output;
		}

		void find(const std::string& s, int i, int* flag) {
			flag[i] = output; 
			if (i == s.length()) return;
			char next = s[i];
			if (child.find(next) != child.end()) {
				// std::cout << "found:" << s << ", " << next << '\n';
				return child[next]->find(s, i + 1, flag);
			}
		}
	}*root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(const std::string& s) { root->insert(s, 0); }
	void find(const std::string& s, int* flag) { root->find(s, 0, flag); }
	void erase(const std::string& s) { root->erase(s, 0); }
};

int Q, flagA[1001], flagB[1001];

int main() {
	freopen("input.txt", "r", stdin);
	std::string q, s;
	char t;
	Trie A, B;
	std::cin >> Q;
	while (Q--) {
		std::cin >> q;
		if (q == "add") {
			std::cin >> t >> s;
			if (t == 'A') A.insert(s);
			else { // B
				std::reverse(s.begin(), s.end());
				B.insert(s);
			}
		}
		else if (q == "delete") {
			std::cin >> t >> s;
			if (t == 'A') A.erase(s);
			else { // B
				std::reverse(s.begin(), s.end());
				B.erase(s);
			}
		}
		else if (q == "find") {
			ll result = 0;
			memset(flagA, 0, sizeof flagA);
			memset(flagB, 0, sizeof flagB);
			std::cin >> s;
			A.find(s, flagA);
			std::reverse(s.begin(), s.end());
			B.find(s, flagB);
			// for (int i = 1; i <= s.length(); ++i) std::cout << flagA[i] << ' ';
			// std::cout << '\n';
			// for (int i = 1; i <= s.length(); ++i) std::cout << flagB[i] << ' ';
			// std::cout << '\n';
			for (int i = 1; i < s.length(); ++i) {
				// std::cout << flagA[i] << flagB[s.length() - i] << '\n';
				result += flagA[i] * flagB[s.length() - i];
			}
			std::cout << result << '\n';
		}
	}
}
