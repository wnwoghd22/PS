#include <iostream>
#include <queue>

const int LEN = 2001;

struct Atom {
    int i, x, y, dir, k, dist, state;
} atoms[LEN];

int N, valid;

struct Collapse {
    int l, r, dist;
    bool operator<(const Collapse& c) const {
        return dist > c.dist;
    }
};

Collapse get_collapse(Atom l, Atom r) {
    if (l.dir == r.dir) return { -1, -1, -1 };
    if (l.dir > r.dir) {
        Atom temp = l;
        l = r;
        r = temp;
    }
    if (l.dir == 0 && r.dir == 1) {
        if (l.x == r.x && l.y < r.y) return { l.i, r.i, r.y - l.y };
    }
    else if (l.dir == 0 && r.dir == 2) {
        if (r.x > l.x && r.y - l.y == r.x - l.x) return { l.i, r.i, (r.y - l.y) * 2 };
    }
    else if (l.dir == 0 && r.dir == 3) {
        if (l.x > r.x && r.y - l.y == l.x - r.x) return { l.i, r.i, (r.y - l.y) * 2 };
    }
    else if (l.dir == 1 && r.dir == 2) {
        if (r.x > l.x && l.y - r.y == r.x - l.x) return { l.i, r.i, (l.y - r.y) * 2 };
    }
    else if (l.dir == 1 && r.dir == 3) {
        if (l.x > r.x && l.y - r.y == l.x - r.x) return { l.i, r.i, (l.y - r.y) * 2 };
    }
    else if (l.dir == 2 && r.dir == 3) {
        if (l.y == r.y && l.x > r.x) return { l.i, r.i, l.x - r.x };
    }
    return { -1, -1, -1 };
}

int solve() {
    std::cin >> N; valid = N;
    std::priority_queue<Collapse> pq;
    for (int i = 0; i < N; ++i) {
        std::cin >> atoms[i].x >> atoms[i].y >> atoms[i].dir >> atoms[i].k;
        atoms[i].i = i;
        atoms[i].dist = 0;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            Collapse c = get_collapse(atoms[i], atoms[j]);
            if (c.dist != -1) pq.push(c);
        }
    }
    while (pq.size()) {
        Collapse c = pq.top(); pq.pop();
        Atom l = atoms[c.l], r = atoms[c.r];
        if ((!l.dist || l.dist == c.dist) && (!r.dist || r.dist == c.dist)) {
            atoms[c.l].dist = atoms[c.r].dist = c.dist;
        }
    }
    int result = 0;

    for (int i = 0; i < N; ++i) {
        if (atoms[i].dist) result += atoms[i].k;
    }

    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}