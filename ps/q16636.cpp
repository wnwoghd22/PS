#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'001;

int N, M;

struct Pos {
    int x, y;
    bool operator<(const Pos& o) const {
        return x == o.x ? y < o.y : x < o.x;
    }
    bool operator==(const Pos& o) const {
        return x == o.x && y == o.y;
    }
};

ll cross(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
    return (ll)(p2.x - p1.x) * (p4.y - p3.y) - (ll)(p2.y - p1.y) * (p4.x - p3.x);
}

struct Seg {
    Pos p1, p2;
    bool operator<(const Seg& o) const {
        ll dir = cross(p1, p2, o.p1, o.p2);
        if (dir == 0) {
            ll ccw = cross(p1, p2, p2, o.p1);
            if (ccw == 0) {
                return p1 == o.p1 ? p2 < o.p2 : p1 < o.p1;
            }
            return ccw > 0;
        }
        return dir > 0;
    }
    bool operator|(const Seg& o) const {
        return !cross(p1, p2, o.p1, o.p2) && !cross(p1, p2, p2, o.p1);
    }
} A[LEN * 3], B[LEN * 3], C[LEN * 3], D[LEN * 3];

int main() {
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        Pos p1, p2, p3;
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

        if (p1 < p2) A[i * 3 + 0] = { p1, p2 };
        else A[i * 3 + 0] = { p2, p1 };
        if (p2 < p3) A[i * 3 + 1] = { p2, p3 };
        else A[i * 3 + 1] = { p3, p2 };
        if (p3 < p1) A[i * 3 + 2] = { p3, p1 };
        else A[i * 3 + 2] = { p1, p3 };
    }
    std::cin >> M;
    for (int i = 0; i < M; ++i) {
        Pos p1, p2, p3;
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

        if (p1 < p2) B[i * 3 + 0] = { p1, p2 };
        else B[i * 3 + 0] = { p2, p1 };
        if (p2 < p3) B[i * 3 + 1] = { p2, p3 };
        else B[i * 3 + 1] = { p3, p2 };
        if (p3 < p1) B[i * 3 + 2] = { p3, p1 };
        else B[i * 3 + 2] = { p1, p3 };
    }
    std::sort(A, A + N * 3);
    std::sort(B, B + M * 3);

    int len1 = 0;
    Seg cur = A[0];
    for (int i = 1; i < N * 3; ++i) {
        if (cur.p1 == cur.p2) {
            cur = A[i];
            continue;
        }

        if (cur | A[i]) {
            if (cur.p2 == A[i].p1) {
                cur.p2 = A[i].p2;
            }
            else if (A[i].p1 < cur.p2) {
                if (!(cur.p1 == A[i].p1)) C[len1++] = { cur.p1, A[i].p1 };
                if (cur.p2 < A[i].p2) cur = { cur.p2, A[i].p2 };
                else cur = { A[i].p2, cur.p2 };
            }
            else {
                if (!(cur.p1 == cur.p2)) C[len1++] = cur;
                cur = A[i];
            }
        }
        else {
            if (!(cur.p1 == cur.p2)) C[len1++] = cur;
            cur = A[i];
        }
    }
    if (!(cur.p1 == cur.p2)) C[len1++] = cur;

    int len2 = 0;
    cur = B[0];
    for (int i = 1; i < M * 3; ++i) {
        if (cur.p1 == cur.p2) {
            cur = B[i];
            continue;
        }

        if (cur | B[i]) {
            if (cur.p2 == B[i].p1) {
                cur.p2 = B[i].p2;
            }
            else if (B[i].p1 < cur.p2) {
                if (!(cur.p1 == B[i].p1)) D[len2++] = { cur.p1, B[i].p1 };
                if (cur.p2 < B[i].p2) cur = { cur.p2, B[i].p2 };
                else cur = { B[i].p2, cur.p2 };
            }
            else {
                if (!(cur.p1 == cur.p2)) D[len2++] = cur;
                cur = B[i];
            }
        }
        else {
            if (!(cur.p1 == cur.p2)) D[len2++] = cur;
            cur = B[i];
        }
    }
    if (!(cur.p1 == cur.p2)) D[len2++] = cur;

    bool flag = true;
    if (len1 == len2) {
        for (int i = 0; i < len1; ++i) {
            if (C[i].p1 == D[i].p1 && C[i].p2 == D[i].p2) continue;
            else {
                flag = false;
                break;
            }
        }
    }
    else flag = false;

    std::cout << (flag ? "yes" : "no");
}