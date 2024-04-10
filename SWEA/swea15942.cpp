#include <iostream>

typedef long long int ll;

class priority_queue {
public:
    ll _size, *heap;
    priority_queue() : _size(0) { heap = new ll[200000]; }
    ~priority_queue() { delete[] heap; }
    void trickle_down(int i) {
        int s = i, l = i * 2, r = i * 2 + 1;
        if (l <= _size && heap[l] > heap[i]) s = l;
        if (r <= _size && heap[r] > heap[s]) s = r;
        if (s != i) {
            ll temp = heap[i];
            heap[i] = heap[s];
            heap[s] = temp;
            trickle_down(s);
        }
    }
    void bubble_up(int i) {
        if (i > 1 && heap[i / 2] < heap[i]) {
            ll temp = heap[i];
            heap[i] = heap[i / 2];
            heap[i / 2] = temp;
            bubble_up(i / 2);
        }
    }
    void push(ll e) {
        heap[++_size] = e;
        bubble_up(_size);
    }
    ll top() { return heap[1]; }
    ll pop() {
        ll result = heap[1];
        heap[1] = heap[_size--];
        trickle_down(1);
        return result;
    }
};

int solve() {
    ll n, k, A, available;
    int result = 0;
    priority_queue u, d, c; // up, down, conquered

    std::cin >> n >> k;
    available = k;
    while (n--) {
        std::cin >> A;
        if (A > k) u.push(-A);
        else d.push(A);
    }

    while (d._size) {
        while (k < d.top()) {
            ++result; k += c.pop() << 1;
        }
        if (available < d.top()) break;
        c.push(d.top()); k -= d.top(); available += d.top(); d.pop();
        while (u._size && available >= -u.top()) {
            d.push(-u.pop());
        }
    }
    if (u._size) return -1;
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) {
        printf("#%d %d\n", t, solve());
    }
}