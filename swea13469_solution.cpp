#include <queue>

class Editor {
	struct Row {
		std::deque<char> l, r;
		int cnt[26];
		int size() { return l.size() + r.size(); }
		void set_cursor(int i) {

			/*std::cout << "\nset cursor: ";
			for (const char s : l) std::cout << s;
			std::cout << '/';
			for (const char s : r) std::cout << s;
			std::cout << '\n';*/
			while (l.size() >= i) {
				r.push_front(l.back());
				l.pop_back();
			}

			/*std::cout << "\nset cursor: ";
			for (const char s : l) std::cout << s;
			std::cout << '/';
			for (const char s : r) std::cout << s;
			std::cout << '\n';*/
			while (l.size() < i - 1 && r.size()) {
				l.push_back(r.front());
				r.pop_front();
			}

			/*std::cout << "\nset cursor: ";
			for (const char s : l) std::cout << s;
			std::cout << '/';
			for (const char s : r) std::cout << s;
			std::cout << '\n';*/
		}
		void insert(char c) {
			l.push_back(c);
			cnt[c - 'a']++;
		}
		void push_front(char c) {
			l.push_front(c);
			cnt[c - 'a']++;
		}
		void push_back(char c) {
			r.push_back(c);
			cnt[c - 'a']++;
		}
		char pop_front() {
			char c = 0;
			if (l.size()) {
				c = l.front();
				l.pop_front();
			}
			else {
				c = r.front();
				r.pop_front();
			}
			cnt[c - 'a']--;
			return c;
		}
		char pop_back() {
			char c = 0;
			if (r.size()) {
				c = r.back();
				r.pop_back();
			}
			else {
				c = l.back();
				l.pop_back();
			}
			cnt[c - 'a']--;
			return c;
		}
	} rows[300];
	int h, w;
	int cur_i;
public:
	Editor() : h(0), w(0), cur_i(0) {}
	Editor(int H, int W, char* s) : h(H), w(W) {
		cur_i = 0;
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < 26; ++j) {
				rows[i].cnt[j] = 0;
			}
		}
		for (int i = 0; s[i]; ++i) {
			rows[i / W].push_back(s[i]);
		}
	}
	char move_cursor(int r, int c) {
		cur_i = r;
		if (!rows[--cur_i].size()) {
			c = w;
			while (!rows[--cur_i].size());
			if (rows[cur_i].size() == w) cur_i++;
		}
		rows[cur_i].set_cursor(c);
		if (rows[cur_i].r.size()) return rows[cur_i].r.front();
		else return '$';
	}
	void insert(int c) {
		rows[cur_i].insert(c);
		for (int i = cur_i; rows[i].size() > w && i < h; ++i) {
			rows[i + 1].push_front(rows[i].pop_back());
		}
		if (rows[cur_i].l.size() == w) {
			rows[++cur_i].set_cursor(1);
		}
	}
	int count_char(char target) {
		int cnt = 0;
		for (const char& c : rows[cur_i].r) {
			if (c == target) ++cnt;
		}
		for (int i = cur_i + 1; i < h; ++i) {
			cnt += rows[i].cnt[target - 'a'];
		}
		return cnt;
	}
} editor;

void init(int H, int W, char mStr[])
{
	editor = Editor(H, W, mStr);
}

void insert(char mChar)
{
	// std::cout << "insert " << mChar << '\n';
	editor.insert(mChar);
}

char moveCursor(int mRow, int mCol)
{
	char c = editor.move_cursor(mRow, mCol);
	// std::cout << "move cursor: " << c << '\n';
	return c;
}

int countCharacter(char mChar)
{
	int cnt = editor.count_char(mChar);
	// std::cout << "count char " << mChar << ": " << cnt << '\n';
	return cnt;
}
