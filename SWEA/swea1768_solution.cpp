#define N 4

struct Result {
    int strike;
    int ball;
    bool operator!=(const Result& r) const { return strike != r.strike || ball != r.ball; }
};

bool candidate[10000];
int buffer[4];
int target[4];
void itoa(int i, int a[]) {
    for (int d = 0; d < 4; ++d) {
        a[d] = i % 10;
        i /= 10;
    }
}

bool isValid(int num[]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i ^ j && num[i] == num[j])
                return false;
    return true;
}

void init() {
    for (int i = 123; i <= 9876; ++i) {
        itoa(i, buffer);
        if (isValid(buffer)) candidate[i] = true;
    }
}

Result compare(int a[], int b[]) {
    Result result;
    result.strike = result.ball = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j && a[i] == b[j]) {
                result.strike++;
                break;
            }
            else if (i ^ j && a[i] == b[j]) {
                result.ball++;
                break;
            }
        }
    }
    return result;
}

// API
extern Result query(int guess[]);

void doUserImplementation(int guess[]) {
    init();
    int i = 123, j;
    while (1) {
        itoa(i, buffer);
        Result q = query(buffer);
        if (q.strike == 4) break;
        for (j = i; j <= 9876; ++j) {
            if (!candidate[j]) continue;
            itoa(j, target);
            if (q != compare(buffer, target)) {
                candidate[j] = false;
            }
        }
        while (i <= 9876 && !candidate[i]) ++i;
    }
    itoa(i, buffer);
    for (j = 0; j < 4; ++j) guess[j] = buffer[j];
}
