#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

typedef long long int ll;
const int MAX = 1'000'000;

int N, M, K;
ll segTree[MAX * 4];
ll segSum[MAX * 4];

void update_diff(int left, int right, ll diff, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		segTree[index] += diff; return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);
}

ll get_diff(int n, int start = 0, int end = N - 1, int index = 1) {
	// if (n > end || n < start) return 0;
	// if (start == end) return segTree[index] + arr[n];
	int mid = (start + end) / 2;
	return segTree[index] + get_diff(n, start, mid, index * 2) + get_diff(n, mid + 1, end, index * 2 + 1);
}

ll get_sum(int left, int right, int index = 1, int start = 1, int end = MAX) {
	if (n > end || n < start) return 0;
	// if (start == end) return segTree[index] + arr[n];
	int mid = (start + end) / 2;
	return segTree[index] + get_diff(n, start, mid, index * 2) + get_diff(n, mid + 1, end, index * 2 + 1);

}

int main() {

}