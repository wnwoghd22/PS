#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const ll MOD = 1e9 + 7;

class Matrix {
private:
    int row, col;
    ll** arr;
public:
    Matrix(int r, int c) : row(r), col(c) {
        arr = new ll * [row];
        for (int i = 0; i < row; ++i) {
            arr[i] = new ll[col];
            for (int j = 0; j < col; ++j) arr[i][j] = 0;
        }
    }
    Matrix(const Matrix& m) : row(m.row), col(m.col) {
        arr = new ll * [row];
        for (int i = 0; i < row; ++i) {
            arr[i] = new ll[col];
            for (int j = 0; j < col; ++j) arr[i][j] = m.arr[i][j];
        }
    }
    ll* const operator[](const size_t i) { return arr[i]; }

    Matrix operator*(const Matrix& m) {
        Matrix result(row, m.col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < m.col; ++j)
                for (int k = 0; k < col; ++k) {
                    result.arr[i][j] += arr[i][k] * m.arr[k][j] % MOD;
                    result.arr[i][j] %= MOD;
                }
        return result;
    }
    Matrix operator%(const ll scalar) {
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.arr[i][j] = arr[i][j] % scalar;
        return result;
    }
    ~Matrix() { for (int i = 0; i < row; ++i) delete[] arr[i]; delete[] arr; }
} *mt[101], *mm[101];

Matrix power(Matrix A, const ll B) {
    if (B == 0) return *mt[0];
    if (B == 1) return A % MOD;
    else {
        Matrix pw = power(A, B / 2);
        return B & 1 ? (pw * pw % MOD * A % MOD) : (pw * pw % MOD);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ll T, N, D, M, a, b, c;
    std::cin >> T >> N >> D;
    mt[0] = new Matrix(N, N);
    mm[0] = new Matrix(N, N);
    for (int i = 0; i < N; ++i) (*mm[0])[i][i] = 1;

    for (int i = 1; i <= T; ++i) {
        mt[i] = new Matrix(N, N);
        std::cin >> M;
        while (M--) {
            std::cin >> a >> b >> c;
            (*mt[i])[a - 1][b - 1] = c;
        }
    }
    for (int i = 1; i <= T; ++i) {
        mm[i] = new Matrix((*mm[i - 1]) * (*mt[i]));
    }

    Matrix result = power(*mm[T], D / T) * (*mm[D % T]) % MOD;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            std::cout << result[i][j] << ' ';
        std::cout << '\n';
    }

    return 0;
}