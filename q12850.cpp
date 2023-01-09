#include <iostream>

typedef long long int ll;
const ll MOD = 1'000'000'007;

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
                for (int k = 0; k < col; ++k)
                    result.arr[i][j] += arr[i][k] * m.arr[k][j], result.arr[i][j] %= MOD;
        return result;
    }
    Matrix operator%(const ll scalar) {
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                result.arr[i][j] = (arr[i][j] + scalar) % scalar;
            }
        return result;
    }
    ~Matrix() { for (int i = 0; i < row; ++i) delete[] arr[i]; delete[] arr; }
};

Matrix power(Matrix A, const ll B, const ll mod = MOD) {
    if (B == 1) return A % mod;
    else {
        Matrix pw = power(A, B / 2, mod);
        return B % 2 ? (pw * pw % mod * A % mod) : (pw * pw % mod);
    }
}

int main() {
    ll N;
    std::cin >> N;
    Matrix A(8, 8);
    A[0][1] = A[0][2] = 1;
    A[1][0] = A[1][2] = A[1][3] = 1;
    A[2][0] = A[2][1] = A[2][3] = A[2][4] = 1;
    A[3][1] = A[3][2] = A[3][4] = A[3][5] = 1;
    A[4][2] = A[4][3] = A[4][5] = A[4][7] = 1;
    A[5][3] = A[5][4] = A[5][6] = 1;
    A[6][5] = A[6][7] = 1;
    A[7][4] = A[7][6] = 1;

    Matrix result = power(A, N);
    std::cout << result[0][0];

    return 0;
}