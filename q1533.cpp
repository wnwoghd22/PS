#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const ll MOD = 1'000'003;

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
};

Matrix power(Matrix A, const ll B) {
    if (B == 1) return A % MOD;
    else {
        Matrix pw = power(A, B / 2);
        return B & 1 ? (pw * pw % MOD * A % MOD) : (pw * pw % MOD);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ll N, S, E, T;
    char c;
    std::cin >> N >> S >> E >> T;
    Matrix A(N * 5, N * 5);
    for (int i = 0; i < N; ++i)
        for (int j = 1; j < 5; ++j)
            A[i * 5 + j][i * 5 + j - 1] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> c;
            int a = c - '0';
            if (a > 0) A[i * 5][j * 5 + a - 1] = 1;
        }
    }
    Matrix result = power(A, T);

    /*for (int i = 0; i < N * 5; ++i) {
        for (int j = 0; j < N * 5; ++j)
            std::cout << result[i][j] << ' ';
        std::cout << '\n';
    }*/
    std::cout << result[(S - 1) * 5][(E - 1) * 5];

    return 0;
}