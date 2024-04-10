#include <iostream>
const int MAX = 30'000;

void swap(int& a, int& b) {
	int temp = a;
	a = b, b = temp;
}

void flip(int block[4][4]) {
	for (int i = 0; i < 4; ++i) {
		swap(block[i][0], block[i][3]);
		swap(block[i][1], block[i][2]);
	}
}
void rotate(int block[4][4]) {
	int temp[4][4];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			temp[j][3 - i] = block[i][j];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			block[i][j] = temp[i][j];
}

int order = 0;
class Trie {
	struct Node {
		Node* next[3];
		int index;
		Node() : index(-1) { next[0] = next[1] = next[2] = 0; }
		~Node() { for (int i = 0; i < 3; ++i) if (next[i]) delete next[i]; }
		int find(int block[4][4], int i) {
			if (i == 16) {
				// std::cout << "found!\n";
				return index;
			}
			int key = block[i / 4][i % 4];
			if (next[key]) return next[key]->find(block, i + 1);
			// std::cout << "not found\n";
			return -1;
		}
		void insert(int block[4][4], int i) {
			if (i == 16) {
				if (!~index) {
					index = order++;
				}
				return;
			}
			int key = block[i / 4][i % 4];
			if (!next[key]) next[key] = new Node;
			next[key]->insert(block, i + 1);
		}
	} *root;
public:
	Trie() { root = new Node; }
	~Trie() { delete root; }
	void insert(int block[4][4]) { root->insert(block, 0); }
	int find(int block[4][4]) { return root->find(block, 0); }
};

class LinkedList {
	struct Node {
		Node* before;
		int v;
		Node(int v) : before(0), v(v) {}
	} *tail = 0;
	int _size = 0;
public:
	int size() { return _size; }
	void clear() {
		_size = 0;
		while (tail) {
			Node* temp = tail;
			tail = tail->before;
			delete temp;
		}
	}
	void push(int i) {
		++_size;
		Node* temp = new Node(i);
		temp->before = tail;
		tail = temp;
	}
	int pop() {
		--_size;
		Node* temp = tail;
		tail = tail->before;
		int result = temp->v;
		delete temp;
		return result;
	}
} stack[MAX];
int height[MAX], diff[MAX], hash_key[MAX], index[MAX];

int buffer[MAX];
void merge(int a[], int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) buffer[k++] = height[a[i]] <= height[a[j]] ? a[i++] : a[j++];
	while (i <= m) buffer[k++] = a[i++];
	while (j <= r) buffer[k++] = a[j++];
	for (k = l; k <= r; ++k) a[k] = buffer[k];
}
void merge_sort(int a[], int l, int r) {
	if (l == r) return;

	int m = l + r >> 1;
	merge_sort(a, l, m);
	merge_sort(a, m + 1, r);
	
	merge(a, l, m, r);
}

int makeBlock(int module[][4][4]) {
	order = 0;
	for (int i = 0; i < MAX; ++i) stack[i].clear();
	Trie hashMap;
	int temp[4][4];

	// preprocess
	for (int i = 0; i < MAX; ++i) {
		index[i] = i;
		int h = 10;
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				temp[j][k] = module[i][j][k];
				if (temp[j][k] < h)
					h = temp[j][k];
			}
		}
		height[i] = h;
		diff[i] = 0;
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				temp[j][k] -= h;
				if (temp[j][k] > diff[i])
					diff[i] = temp[j][k];
			}
		}
		/*if (i == 0) {
			std::cout << "\npreprocess: ";
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					std::cout << temp[j][k];
			std::cout << '\n';
		}*/
		for (int j = 0; j < 4; ++j) {
			if (j) rotate(temp);
			int hash = hashMap.find(temp);
			if (hash == -1) {
				if (j == 3) {
					hashMap.insert(temp);
					hash_key[i] = order - 1;
				}
			}
			else {
				hash_key[i] = hash;
				break;
			}
		}
	}
	// std::cout << "hash size: " << order << '\n';
	// sort
	merge_sort(index, 0, MAX - 1);
	for (int i = 0; i < MAX; ++i)
		// std::cout << index[i] << ' ' << height[index[i]] << ' ' << hash_key[index[i]] << '\n',
		stack[hash_key[index[i]]].push(index[i]);

	// greedy step
	int result = 0;
	for (int i = 0; i < MAX; ++i) {
		while (stack[i].size()) {
			int cur = stack[i].pop();
			// std::cout << cur << ' ' << height[cur] << '\n';
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					temp[j][k] = diff[cur] - (module[cur][j][k] - height[cur]);
			/*if (cur == 0) {
				std::cout << "\ngreedy step: ";
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						std::cout << temp[j][k];
				std::cout << '\n';
			}*/

			flip(temp);
			bool flag = false;
			for (int j = 0; j < 4; ++j) {
				if (j) rotate(temp);
				int hash = hashMap.find(temp);
				if (~hash) {
					if (stack[hash].size()) {
						int target = stack[hash].pop();
						result += height[cur] + height[target] + diff[cur];
						flag = true;
						break;
					}
				}
			}
			if (!flag) break;
		}
	}
	return result;
}