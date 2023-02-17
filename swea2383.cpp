#include <iostream>
#include <queue>

int people_count, people_pos[10][2];
int door_count, door_len[2], door_pos[2][2];
int dist[10][2];

int solve() {
    int N, A, min_time = 1e9;
    std::priority_queue<int> waitA, waitB;
    std::queue<int> processA, processB;
    std::cin >> N;
    people_count = door_count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> A;
            if (A == 1) {
                people_pos[people_count][0] = i;
                people_pos[people_count][1] = j;
                ++people_count;
            }
            if (A > 1) {
                door_pos[door_count][0] = i;
                door_pos[door_count][1] = j;
                door_len[door_count] = A;
                ++door_count;
            }
        }
    }
    // std::cout << people_count << ' ' << door_count << '\n';
    for (int i = 0; i < people_count; ++i) {
        dist[i][0] = abs(people_pos[i][0] - door_pos[0][0]) + abs(people_pos[i][1] - door_pos[0][1]);
        dist[i][1] = abs(people_pos[i][0] - door_pos[1][0]) + abs(people_pos[i][1] - door_pos[1][1]);
    }
    for (int i = 0; i < (1 << people_count); ++i) {
        int cur_time = 0, cur_cnt = 0;
        for (int j = 0; j < people_count; ++j) {
            if (i & (1 << j)) waitA.push(-dist[j][0]);
            else waitB.push(-dist[j][1]);
        }
        while (cur_cnt < people_count) {
            ++cur_time;
            while (processA.size() && cur_time - processA.front() >= door_len[0]) processA.pop(), ++cur_cnt;
            while (processB.size() && cur_time - processB.front() >= door_len[1]) processB.pop(), ++cur_cnt;
            while (waitA.size() && processA.size() < 3 && -waitA.top() <= cur_time) waitA.pop(), processA.push(cur_time);
            while (waitB.size() && processB.size() < 3 && -waitB.top() <= cur_time) waitB.pop(), processB.push(cur_time);
        }
        if (cur_time < min_time) min_time = cur_time;
    }
    return min_time + 1;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}