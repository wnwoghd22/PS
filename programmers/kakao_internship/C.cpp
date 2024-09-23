#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAX = 6 * 6 * 6 * 6 * 6;
const int LEN = 5;

int N, len;
vector<int> answer;

int num[10][6], A[LEN], B[LEN], C;
int a[MAX], b[MAX];

int idx = 0;
void get_sums(int arr[MAX], int dices[LEN], int i, int s) {
	if (i == N) {
		arr[idx++] = s;
		return;
	}
	for (int j = 0; j < 6; ++j)
		get_sums(arr, dices, i + 1, s + num[dices[i]][j]);
}


int check() {
	idx = 0; get_sums(a, A, 0, 0);
	idx = 0; get_sums(b, B, 0, 0);
	sort(a, a + len); sort(b, b + len);
	int cnt = 0;
	for (int i = 0, j = 0; i < len; ++i) {
		while (j < len && b[j] < a[i]) ++j;
		cnt += j;
	}
	return cnt;
}

void dfs(int i, int k, int b) {
	if (i == N) {
		for (int j = 0, ia = 0, ib = 0; j < N * 2; ++j) {
			if (b & 1 << j) A[ia++] = j;
			else B[ib++] = j;
		}
		int cur = check();
		if (cur > C) {
			C = cur;
			for (int i = 0; i < N; ++i)
				answer[i] = A[i] + 1;
		}
		return;
	}
	if (k == N * 2) return;
	dfs(i, k + 1, b);
	dfs(i + 1, k + 1, b | 1 << k);
}

vector<int> solution(vector<vector<int>> dice) {
	N = dice.size() >> 1;
	len = pow(6, N);
	answer.resize(N);
	for (int i = 0; i < dice.size(); ++i)
		for (int j = 0; j < 6; ++j)
			num[i][j] = dice[i][j];

	dfs(0, 0, 0);

	return answer;
}