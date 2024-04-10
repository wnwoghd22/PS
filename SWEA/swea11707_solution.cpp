#include <queue>
#include <map>
#include <set>
#include <string>

const int USER_COUNT = 2000;
const int WORD_COUNT = 4000;
const int QUERY_COUNT = 50000;

struct Query {
	int time;
	std::string word;
};

int order;
std::deque<Query> dq[USER_COUNT];	// monotone queue trick
std::map<std::string, int> word_map; // word-order map

int error_order;
std::map<std::string, int> errors[WORD_COUNT];	// if error-correct pair found
std::set<int> user_sets[QUERY_COUNT];
std::set<std::string> database[WORD_COUNT];

void init(int n) {
	order = error_order = 0;
	for (std::deque<Query>& q : dq) q.clear();
	word_map.clear();
	for (std::map<std::string, int>& error : errors) error.clear();
	for (std::set<int>& user_set : user_sets) user_set.clear();
	for (std::set<std::string>& record : database) record.clear();
}

bool is_pair(std::string a, std::string b) {
	if (b.length() > a.length()) std::swap(a, b);
	if (a.length() == b.length()) {
		int error_rate = 0;
		for (int i = 0; i < a.length(); ++i)
			if (a[i] != b[i]) error_rate++;
		return error_rate == 1;
	}
	else if (a.length() - b.length() == 1) {
		int match_rate = 0;
		for (int i = 0; i < b.length(); ++i) {
			if (a[i] != b[i]) break;
			match_rate++;
		}
		for (int i = a.length(); i > 0; --i) {
			if (a[i] != b[i - 1]) break;
			match_rate++;
		}
		return match_rate >= b.length();
	}
	return 0;
}

int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
	std::string word(searchWord);
	if (word_map.find(word) == word_map.end()) {
		word_map[word] = order++;
	}
	mId--;
	while (dq[mId].size() && dq[mId].front().time < searchTimestamp - 10) dq[mId].pop_front();
	for (Query& q : dq[mId]) {
		if (is_pair(q.word, word)) {
			if (errors[word_map[q.word]].find(word) == errors[word_map[q.word]].end()) { // error-pair found first
				errors[word_map[q.word]][word] = error_order++;
			}
			int error_pair_num = errors[word_map[q.word]][word];
			if (user_sets[error_pair_num].find(mId) == user_sets[error_pair_num].end()) { // new user
				user_sets[error_pair_num].insert(mId);
				if (user_sets[error_pair_num].size() == 3) { // register
					database[word_map[q.word]].insert(word);
				}
			}
		}
	}
	dq[mId].push_back({ searchTimestamp, word });

	int cnt = 0;
	for (std::string s : database[word_map[word]]) {
		for (int i = 0; i < s.length(); ++i)
			correctWord[cnt][i] = s[i];
		cnt++;
	}

	return cnt;
}