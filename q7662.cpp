#include <iostream>
#include <cmath>

class double_ended_priority_queue {
private:
	int *elements;
	int _size;
	void up_heapify(int idx) {
		bool flag = (int)log2(idx) & 1;
		while (idx > 3) {
			if ((flag && elements[idx] > elements[idx / 4]) || // max layer
				(!flag && elements[idx] < elements[idx / 4])) { // min layer
				int temp = elements[idx];
				elements[idx] = elements[idx / 4];
				elements[idx / 4] = temp;
				idx /= 4;
			}
			else break;
		}
	}
	void up_heap(int idx) {
		if (idx == 1) return;
		bool flag = (int)log2(idx) & 1;
		if ((flag && elements[idx] < elements[idx / 2]) || // max layer, if last e is smaller than min
			(!flag && elements[idx] > elements[idx / 2])) { // min layer, if last e is bigger than max
			int temp = elements[idx];
			elements[idx] = elements[idx / 2];
			elements[idx / 2] = temp;
			idx /= 2;
		}
		up_heapify(idx);
	}
	int get_min_index(int idx) {
		int result = 0;
		int current = elements[idx];

		// compare children
		for (int i = 0; i < 2; ++i)
			if (idx * 2 + i <= _size && elements[idx * 2 + i] < current)
				current = elements[idx * 2 + i], result = idx * 2 + i;

		// compare grand children
		for (int i = 0; i < 4; ++i)
			if (idx * 4 + i <= _size && elements[idx * 4 + i] < current)
				current = elements[idx * 4 + i], result = idx * 4 + i;

		return result;
	}
	int	get_max_index(int idx) {
		int result = 0;
		int current = elements[idx];

		// compare children
		for (int i = 0; i < 2; ++i)
			if (idx * 2 + i <= _size && elements[idx * 2 + i] > current)
				current = elements[idx * 2 + i], result = idx * 2 + i;

		// compare grand children
		for (int i = 0; i < 4; ++i)
			if (idx * 4 + i <= _size && elements[idx * 4 + i] > current)
				current = elements[idx * 4 + i], result = idx * 4 + i;

		return result;
	}
	void down_heap(int idx) {
		while (true) {
			bool flag = (int)log2(idx) & 1;
			int next = flag ? get_max_index(idx) : get_min_index(idx);
			if (!next) break;
			int temp = elements[idx];
			elements[idx] = elements[next];
			elements[next] = temp;
			idx = next;
		}
	}
public:
	double_ended_priority_queue() : _size(0) { elements = new int[1'000'001]; }
	~double_ended_priority_queue() { delete[] elements; }
	void push(int i) {
		elements[++_size] = i;
		up_heap(_size);
	}
	int pop_front() {
		if (_size == 0) return -1;
		int result = elements[1];
		elements[1] = elements[_size--];
		down_heap(1);
		return result;
	}
	int pop_back() {
		if (_size == 0) return -1;
		if (_size == 1) return pop_front();
		int max_index = 2;
		if (_size >= 3)
			max_index = elements[2] > elements[3] ? 2 : 3;
		int result = elements[max_index];
		elements[max_index] = elements[_size--];
		down_heap(max_index);
		return result;
	}
	int size() { return _size; }
};

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		double_ended_priority_queue Q;
		int k;
		std::cin >> k;
		while (k--) {
			char query; int n;
			std::cin >> query >> n;
			if (query == 'I') {
				Q.push(n);
			}
			if (query == 'D') {
				if (Q.size()) {
					int num = n == -1 ? Q.pop_front() : Q.pop_back();
					std::cout << num << '\n';
				}
			}
		}
		if (Q.size()) {
			int max = Q.pop_back();
			int min = Q.size() ? Q.pop_front() : max;
			std::cout << max << ' ' << min << '\n';
		}
		else std::cout << "EMPTY\n";
	}
}