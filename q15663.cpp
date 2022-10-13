#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

#define MAX_N 8

int arr[MAX_N];
bool check[MAX_N];
int N, M;
vector<int> v;
set<string> s;

void dfs() {
    if (v.size() == M) {
        string str = "";
        for (const int& e : v) {
            str += to_string(e) + ' ';
        }
        str += '\n';
        if (s.find(str) == s.end()) {
            std::cout << str;
            s.insert(str);
        }
        return;
    }

    for (int j = 0; j < N; ++j) {
        if (!check[j] && arr[j] != 0) {
            v.push_back(arr[j]);
            check[j] = true;
            dfs();
            check[j] = false;
            v.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr + N);

    dfs();

    return 0;
}