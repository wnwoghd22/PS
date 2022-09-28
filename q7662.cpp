#include <iostream>
#include <cmath>

typedef long long int ll;

class double_ended_priority_queue {
private:
	ll* elements;
	int _size;

	void swap(int a, int b) {
		ll temp = elements[a];
		elements[a] = elements[b];
		elements[b] = temp;
	}
	int get_level(int idx) { return (int)log2(idx); }
	int get_min_index(int idx) {
		if (_size < idx * 2) return 0;

		int result = idx * 2;
		ll current = elements[result];

		// compare children
		if (idx * 2 + 1 <= _size && elements[idx * 2 + 1] < current)
			current = elements[idx * 2 + 1], result = idx * 2 + 1;

		// compare grand children
		for (int i = 0; i < 4; ++i)
			if (idx * 4 + i <= _size && elements[idx * 4 + i] < current)
				current = elements[idx * 4 + i], result = idx * 4 + i;

		return result;
	}
	int	get_max_index(int idx) {
		if (_size < idx * 2) return 0;

		int result = idx * 2;
		ll current = elements[result];

		// compare children
		if (idx * 2 + 1 <= _size && elements[idx * 2 + 1] > current)
			current = elements[idx * 2 + 1], result = idx * 2 + 1;

		// compare grand children
		for (int i = 0; i < 4; ++i)
			if (idx * 4 + i <= _size && elements[idx * 4 + i] > current)
				current = elements[idx * 4 + i], result = idx * 4 + i;

		return result;
	}
	void trickle_down_min(int idx) {
		int next = get_min_index(idx);
		if (next) { // has children
			if (next >= idx * 4) { // grand child
				if (elements[next] < elements[idx]) {
					swap(idx, next);
					if (elements[next] > elements[next / 2]) swap(next, next / 2);
					trickle_down_min(next);
				}
			}
			else { // child
				if (elements[next] < elements[idx])
					swap(idx, next);
			}
		}
	}
	void trickle_down_max(int idx) {
		int next = get_max_index(idx);
		if (next) { // has children
			if (next >= idx * 4) { // grand child
				if (elements[next] > elements[idx]) {
					swap(idx, next);
					if (elements[next] < elements[next / 2]) swap(next, next / 2);
					trickle_down_max(next);
				}
			}
			else { // child
				if (elements[next] > elements[idx])
					swap(idx, next);
			}
		}

	}
	void trickle_down(int idx) {
		if (get_level(idx) & 1) trickle_down_max(idx);
		else trickle_down_min(idx);
	}
	void bubble_up_min(int idx) {
		if (idx > 3 && elements[idx] < elements[idx / 4]) {
			swap(idx, idx / 4);
			bubble_up_min(idx / 4);
		}
	}
	void bubble_up_max(int idx) {
		if (idx > 3 && elements[idx] > elements[idx / 4]) {
			swap(idx, idx / 4);
			bubble_up_max(idx / 4);
		}
	}
	void bubble_up(int idx) {
		if (get_level(idx) & 1) { // max level
			if (idx > 1 && elements[idx] < elements[idx / 2]) { // has parent
				swap(idx, idx / 2);
				bubble_up_min(idx / 2);
			}
			else bubble_up_max(idx);
		}
		else {
			if (idx > 1 && elements[idx] > elements[idx / 2]) { // has parent
				swap(idx, idx / 2);
				bubble_up_max(idx / 2);
			}
			else bubble_up_min(idx);
		}
	}
public:
	double_ended_priority_queue() : _size(0) { elements = new ll[1'000'001]; }
	~double_ended_priority_queue() { delete[] elements; }
	void push(ll i) {
		elements[++_size] = i;
		bubble_up(_size);
	}
	ll pop_front() {
		if (_size == 0) return -1;
		ll result = elements[1];
		elements[1] = elements[_size--];
		trickle_down(1);
		return result;
	}
	ll pop_back() {
		if (_size == 0) return -1;
		if (_size == 1) return pop_front();
		int max_index = 2;
		if (_size >= 3)
			max_index = elements[2] > elements[3] ? 2 : 3;
		ll result = elements[max_index];
		elements[max_index] = elements[_size--];
		trickle_down(max_index);
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
			char query; ll n;
			std::cin >> query >> n;
			if (query == 'I') {
				Q.push(n);
			}
			if (query == 'D') {
				if (Q.size()) {
					ll num = n == -1 ? Q.pop_front() : Q.pop_back();
					std::cout << num << '\n';
				}
			}
		}
		if (Q.size()) {
			ll max = Q.pop_back();
			ll min = Q.size() ? Q.pop_front() : max;
			std::cout << max << ' ' << min << '\n';
		}
		else std::cout << "EMPTY\n";
	}
}