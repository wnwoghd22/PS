#include <iostream>

int A[500'001], temp[500'001];
int K, current = 0;
int result = -1;

void merge(int l, int mid, int r) {
    int i = l, j = mid + 1, t = 1;
    while (i <= mid && j <= r) {
        if (A[i] <= A[j]) temp[t++] = A[i++];
        else temp[t++] = A[j++];
    }
    while (i <= mid) temp[t++] = A[i++];
    while (j <= r) temp[t++] = A[j++];

    i = l, t = 1;

    while (i <= r) {
        A[i++] = temp[t++];
        current++;
        if (K == current) result = A[i - 1];
    }
}

void mergeSort(int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSort(l, mid);
        mergeSort(mid + 1, r);
        merge(l, mid, r);
    }
}

int main() {
    int N;
    std::cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        std::cin >> A[i];
    }
    mergeSort(1, N);

    std::cout << result;
}