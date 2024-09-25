#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

const int LEN = 10'001;
const int MAX_Q = 10700;
int N, K;
int children[LEN][20];
int _size[LEN];
int q;

int compare(int a, int b) {
	char op;
	assert(++q <= MAX_Q);
	std::cout << "? " << a << ' ' << b << std::endl;
	std::cin >> op;
	return op == '<' ? a : b;
}

struct Comp {
	bool operator()(int a, int b) {
		return _size[a] == _size[b] ? a > b :  _size[a] > _size[b];
	}
};

int main() {
	std::cin >> N >> K;

	std::vector<int> result;
	std::priority_queue<int, std::vector<int>, Comp> pq;

	for (int i = 1; i <= N; ++i) pq.push(i);

	while (result.size() != K) {
		while (pq.size() != 1) {
			int a = pq.top(); pq.pop();
			int b = pq.top(); pq.pop();

			if (compare(a, b) == a) {
				children[a][_size[a]++] = b;
				pq.push(a);
			}
			else {
				children[b][_size[b]++] = a;
				pq.push(b);
			}
		}
		int max = pq.top(); pq.pop();
		result.push_back(max);

		for (int i = 0; i < _size[max]; ++i) pq.push(children[max][i]);
	}

	std::cout << "! ";
	for (const int& i : result) std::cout << i << ' ';
	std::cout << std::endl;
}