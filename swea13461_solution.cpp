#define MAX_N (10000)
#define MAX_M (10)

#include <iostream>

typedef unsigned long long ull;
int n, m;

struct Bitmap {
	int bit[4];
	Bitmap() { for (int i = 0; i < 4; ++i) bit[i] = 0; }
	Bitmap(char image[MAX_M][MAX_M]) {
		for (int i = 0; i < 4; ++i) bit[i] = 0;
		int x = 0, y = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				bit[x] |= image[i][j] << y;
				++y;
				if (y == m * 3) {
					y = 0;
					++x;
				}
			}
		}
	}
	Bitmap(const Bitmap& b) { for (int i = 0; i < 4; ++i) bit[i] = b.bit[i]; }
	bool operator==(const Bitmap& r) const {
		for (int i = 0; i < 4; ++i)
			if (bit[i] != r.bit[i])
				return false;
		return true;
	}
} bitmaps[MAX_N];

class HashMap {
	struct Node {
		Bitmap k;
		int v;
		int next;
		Node() : k(), v(-1), next(-1) {}
	} nodes[MAX_N];
	int size;
	int bucket[MAX_N];
	int djb2(const Bitmap& b) {
		ull key = 5381;
		for (int i = 0; i < 4; ++i)
			key = ((key << 5) + key + b.bit[i]) % MAX_N;
		return key;
	}
public:
	HashMap() { clear(); }
	void clear() {
		size = 0;
		for (int i = 0; i < MAX_N; ++i) {
			bucket[i] = -1;
			nodes[i] = Node();
		}
	}
	void insert(const Bitmap& b, int i) {
		int key = djb2(b);
		if (~bucket[key]) {
			int ni = bucket[key];
			while (1) {
				if (nodes[ni].k == b) return;
				if (~nodes[ni].next) ni = nodes[ni].next;
				else break;
			}
			nodes[ni].next = size++;
			ni = nodes[ni].next;
			nodes[ni].k = b;
			nodes[ni].v = i;
		}
		else {
			int ni = bucket[key] = size++;
			nodes[ni].k = b;
			nodes[ni].v = i;
		}
	}
	int find(const Bitmap& b) {
		int key = djb2(b);
		if (~bucket[key]) {
			int ni = bucket[key];
			while (1) {
				if (nodes[ni].k == b) return nodes[ni].v;
				if (~nodes[ni].next) ni = nodes[ni].next;
				else break;
			}
		}
		return -1;
	}
} map;

void init(int N, int M, char mImageList[MAX_N][MAX_M][MAX_M])
{
	n = N, m = M;
	map.clear();
	for (int k = 0; k < n; ++k) {
		bitmaps[k] = Bitmap(mImageList[k]);
		map.insert(bitmaps[k], k);

		/*for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j)
				std::cout << (int)mImageList[k][i][j];
			std::cout << '\n';
		}
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 30; ++j) {
				std::cout << !!(bitmaps[k].bit[i] & 1 << j);
			}
			std::cout << '\n';
		}*/

	}
}
int findImage(char mImage[MAX_M][MAX_M])
{
	Bitmap b(mImage);
	int result;
	if (~(result = map.find(b))) return result + 1;
	int min_index = n;
	for (int i = 0; i < m * m; ++i) {
		int x = i / (m * 3);
		int y = i % (m * 3);
		b.bit[x] ^= 1 << y;
		if (~(result = map.find(b))) {
			if (result < min_index)
				min_index = result;
		}
		b.bit[x] ^= 1 << y;
	}
	if (min_index != n) return min_index + 1;

	min_index = n;
	for (int i = 0; i < m * m; ++i) {
		int x = i / (m * 3);
		int y = i % (m * 3);
		b.bit[x] ^= 1 << y;
		for (int j = i + 1; j < m * m; ++j) {
			int nx = j / (m * 3);
			int ny = j % (m * 3);
			b.bit[nx] ^= 1 << ny;
			if (~(result = map.find(b))) {
				if (result < min_index)
					min_index = result;
			}
			b.bit[nx] ^= 1 << ny;
		}
		b.bit[x] ^= 1 << y;
	}
	if (min_index != n) return min_index + 1;

	return 0;
}