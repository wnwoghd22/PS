#include <iostream>
#include <random>
#include <vector>

using namespace std;
int perm_[100001], n_;
int countq_;
int compare(int x, int y) {
    if ((x < 1) || (x > n_) || (y < 1) || (y > n_)) {
        printf("-2\n");
        exit(0);
    }
    countq_++;
    if (countq_ > 3e6) {
        printf("-3\n");
        exit(0);
    }
    if (perm_[x - 1] > perm_[y - 1]) return x;
    return y;
}

#include "biggest.cpp"
int main() {
    int k, i, type;
    cin >> n_ >> k >> type;

    if (type == 0)
    {
        for (i = 0; i < n_; i++) {
            cin >> perm_[i];
        }
    }
    else
    {
        int seed;
        cin >> seed;

        mt19937 rng(seed);

        for (int i = 0; i < n_; i++)perm_[i] = i + 1;
        shuffle(perm_, perm_ + n_, rng);
    }

    // for (int i = 0; i < n_; ++i) cout << perm_[i] << ' ';
    // cout << '\n';

    vector <int> ans = biggest(n_, k);
    for (i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    cout << "count: " << countq_ << endl;
    return 0;

    /* int k, i;
    cin >> n_ >> k;

    for (int seed = 0; seed < 200; ++seed) {
        mt19937 rng(seed);

        for (int i = 0; i < n_; i++)perm_[i] = i + 1;
        shuffle(perm_, perm_ + n_, rng);

        countq_ = 0;
        vector <int> ans = biggest(n_, k);
        // for (i = 0; i < ans.size(); i++) {
        //     cout << ans[i] << " ";
        // }
        // cout << endl;
        cout << "count: " << countq_ - n_ + 1 << endl;
    }

    return 0; */
}
