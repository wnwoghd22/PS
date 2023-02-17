#include <iostream>

int map[20][20];
int N, X;

int check_slope() {
    int count = 0;
    for (int i = 0; i < N; ++i) {
        int flag = 1, stack = 1, cur = map[i][0];
        for (int j = 1; j < N; ++j) {
            int next = map[i][j];
            if (next == cur) {
                ++stack;
            }
            else if (next == cur + 1) {
                if (stack >= X) {
                    cur = next;
                    stack = 1;
                }
                else flag = false;
            }
            else if (next == cur - 1) {
                if (stack >= 0) {
                    cur = next;
                    stack = -X + 1;
                }
                else flag = false;
            }
            else flag = false;
        }
        if (stack < 0) flag = false;
        if (flag) ++count;

        flag = 1, stack = 1, cur = map[0][i];
        for (int j = 1; j < N; ++j) {
            int next = map[j][i];
            if (next == cur) {
                ++stack;
            }
            else if (next == cur + 1) {
                if (stack >= X) {
                    cur = next;
                    stack = 1;
                }
                else flag = false;
            }
            else if (next == cur - 1) {
                if (stack >= 0) {
                    cur = next;
                    stack = -X + 1;
                }
                else flag = false;
            }
            else flag = false;
        }
        if (stack < 0) flag = false;
        if (flag) ++count;
    }
    return count;
}

int solve() {
    std::cin >> N >> X;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> map[i][j];
        }
    }
    return check_slope();
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}