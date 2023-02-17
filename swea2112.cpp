#include <iostream>

const int INF = 1e9;
int check[13];
int map[20][13];
int D, W, K;
int max;

bool get_attr(int w, int d) {
    if (check[d] == 1) return 1; // B
    if (check[d] == -1) return 0; // A
    return map[w][d];
}

bool check_attr() {
    for (int i = 0; i < W; ++i) {
        int result = 0, top = -1, max = 0;
        for (int j = 0; j < D; ++j) {
            int a = get_attr(i, j);
            if (a != top) {
                top = a;
                result = 1;
            }
            else ++result;
            if (result > max) max = result;
        }
        if (max < K) return false;
    }
    return true;
}

int dfs(int i, int k) {
    if (check_attr()) return max = std::min(max, k);
    if (i == D) return INF;

    int result = K;
    int r1 = dfs(i + 1, k);
    if (r1 < result) result = r1;
    if (k == max) return result;

    check[i] = -1; // inject A
    int r2 = dfs(i + 1, k + 1);
    if (r2 < result) result = r2;
    if (k + 1 == max) {
        check[i] = 0;
        return result;
    }
    check[i] = 1; // inject B
    int r3 = dfs(i + 1, k + 1);
    if (r3 < result) result = r3;

    check[i] = 0;
    return result;
}

int solve() {
    std::cin >> D >> W >> K;
    for (int i = 0; i < D; ++i) {
        check[i] = 0;
        for (int j = 0; j < W; ++j) {
            std::cin >> map[j][i];
        }
    }
    max = INF;
    return dfs(0, 0);
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}