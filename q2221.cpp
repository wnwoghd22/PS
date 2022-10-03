#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>

const int MAX = 100'001;
std::vector<int> tree[MAX];
int parent[MAX];
int level[MAX];
int tree_width[MAX];

int incoming[MAX];
std::vector<int> graph[MAX];
int N;
struct Comp {
    bool operator()(int a, int b) { 
        return level[a] < level[b] ? true :
            (level[a] == level[b] &&
            (tree[parent[a]].size() > tree[parent[b]].size() ? true :
            (tree[parent[a]].size() == tree[parent[b]].size() &&
            parent[a] < parent[b])));
    }
};

void make_tree(int v = 0, int height = 0) {
    level[v] = height;
    ++tree_width[height];
    for (const int& u : tree[v]) {
        make_tree(u, height + 1);
    }
}

/// <summary>
/// ���Ǻ� ��������
/// <para>O(N log N)</para>
/// 
/// ���ð� ó�� ������ ���� ����ŭ�� ������.
/// ����, Ʈ�������� ��� ���� �� �켱������ ���� ������.
/// </summary>
/// <param name="capacity">���ð� �ذ��� �� �ִ� ������ ��(������ ��)</param>
/// <returns>��� �ð�</returns>
int conditional_topological_sort(int capacity) {
    static std::priority_queue<int, std::vector<int>, Comp> delayed;
    static std::queue<int> Q;
    static int currentIncoming[MAX];
    int time = 0;

    memcpy(currentIncoming, incoming, sizeof incoming);

    for (int i = 1; i <= N; ++i) {
        if (!currentIncoming[i])
            delayed.push(i);
    }

    while (!delayed.empty()) {
        for (int i = 0; i < capacity && !delayed.empty(); ++i) {
            Q.push(delayed.top()); delayed.pop();
        }
        while (!Q.empty()) {
            int v = Q.front(); Q.pop();

            for (const int& u : graph[v]) {
                if (!--currentIncoming[u]) {
                    delayed.push(u);
                }
            }
        }
        ++time;
    }
    return time;
}

/// <summary>
/// �̺�Ž��
/// <para>O(log N) * O(N log N)</para>
/// 
/// �� ��� �ð��� Ʈ���� ���� ���Ͽ��� �Ѵ�.
/// </summary>
/// <param name="width">Ʈ���� ��</param>
/// <param name="height">Ʈ���� ����</param>
/// <returns>������ �ּ� ��</returns>
int binary_search(const int width, const int height) {
    int l = ceil(double(N) / height), r = width, result = width;

    while (l <= r) {
        int mid = (l + r) / 2;
        int val = conditional_topological_sort(mid);

        if (val <= height) {
            result = std::min(result, mid);
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return result;
}

int main() {
    std::cin >> N;
    for (int a, i = 1; i <= N; ++i) {
        std::cin >> a;
        if (a == -1) {
            parent[i] = 0;
            tree[0].push_back(i);
        }
        else {
            parent[i] = a;
            tree[a].push_back(i);
            graph[i].push_back(a);
            ++incoming[a];
        }
    }
    if (N == 1) {
        std::cout << 1 << '\n' << 0;
        return 0;
    }

    make_tree();

    int height = *std::max_element(level, level + N + 1);
    int width = *std::max_element(tree_width, tree_width + N + 1);

    int result = binary_search(width, height);

    // std::cout << height << ' ' << width << ' ' << result << '\n';

    std::cout << height << '\n' << N - result;
}