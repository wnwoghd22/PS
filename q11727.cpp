#include <iostream>

#define LL long long int

class Matrix {
private:
    int row, col;
    LL** arr;
public:
    Matrix(int r, int c) : row(r), col(c) {
        arr = new LL * [row];
        for (int i = 0; i < row; ++i) {
            arr[i] = new LL[col];
            for (int j = 0; j < col; ++j) arr[i][j] = 0;
        }
    }
    Matrix(const Matrix& m) : row(m.row), col(m.col) {
        arr = new LL * [row];
        for (int i = 0; i < row; ++i) {
            arr[i] = new LL[col];
            for (int j = 0; j < col; ++j) arr[i][j] = m.arr[i][j];
        }
    }
    LL* const operator[](const size_t i) { return arr[i]; }

    Matrix operator*(const Matrix& m) {
        Matrix result(row, m.col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < m.col; ++j)
                for (int k = 0; k < col; ++k)
                    result.arr[i][j] += arr[i][k] * m.arr[k][j];
        return result;
    }
    Matrix operator%(const LL scalar) {
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.arr[i][j] = arr[i][j] % scalar;
        return result;
    }
    ~Matrix() { for (int i = 0; i < row; ++i) delete[] arr[i]; delete[] arr; }
};

Matrix power(Matrix A, const LL B, const LL mod) {
    if (B == 1) return A % mod;
    else {
        Matrix pw = power(A, B / 2, mod);
        return B % 2 ? (pw * pw % mod * A % mod) : (pw * pw % mod);
    }
}

int main() {
    LL N;
    std::cin >> N;
    Matrix A(2, 2);
    A[0][0] = 1, A[0][1] = 2, A[1][0] = 1, A[1][1] = 0;
    std::cout << power(A, N, 10'007)[0][0];

    return 0;
}