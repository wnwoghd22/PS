#include <iostream>

typedef long long int ll;

class TrieNode {
public:
    char element;
    bool isWord;
    int numOfChildren;
    TrieNode* children[26];
    TrieNode(char c) : element(c), isWord(false), numOfChildren(0) {
        for (int i = 0; i < 26; ++i) children[i] = 0;
    }
    ll dfs(ll input = 0) const {
        ll result = isWord ? input : 0;

        // if (isWord) std::cout << element << ' ' << input << '\n';

        for (int i = 0; i < 26; ++i) {
            if (children[i] != 0) {
                result += children[i]->dfs(!element || isWord || numOfChildren > 1 ? input + 1 : input);
            }
        }

        return result;
    }
    ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
            if (children[i]) delete children[i];
        }
    }
};

int main() {
    int N, T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;
        TrieNode root(0);
        for (int n = 0; n < N; ++n) {
            std::string s;
            std::cin >> s;

            TrieNode* current = &root;
            for (int i = 0; i < s.length(); ++i) {
                if (current->children[s[i] - 'a']) {
                    current = current->children[s[i] - 'a'];
                }
                else {
                    current->numOfChildren++;
                    current->children[s[i] - 'a'] = new TrieNode(s[i]);
                    current = current->children[s[i] - 'a'];
                }
                if (i == s.length() - 1) current->isWord = true;
            }
        }
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << (double)root.dfs() / N << '\n';
    }
}