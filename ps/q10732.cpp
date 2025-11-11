#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>

const double TOL = 1e-6;

int cnt = 0;

struct Pos {
	int id, q_id;
	double x, y;
	bool operator<(const Pos& o) const {
		if (std::abs(x - o.x) < TOL) return y < o.y;
		return x < o.x;
	}
};

struct Segment {
	Pos s, e;
	Pos intersect_at(const Segment& o) const {
		// compute intersection of two segments (s--e) and (o.s--o.e)
		// return {-1,-1,-1,-1} in x/y to indicate no intersection
		auto cross = [](double ax, double ay, double bx, double by) {
			return ax * by - ay * bx;
		};
		double x1 = s.x, y1 = s.y;
		double x2 = e.x, y2 = e.y;
		double x3 = o.s.x, y3 = o.s.y;
		double x4 = o.e.x, y4 = o.e.y;
		double dx1 = x2 - x1, dy1 = y2 - y1;
		double dx2 = x4 - x3, dy2 = y4 - y3;
		double denom = cross(dx1, dy1, dx2, dy2);
		if (std::abs(denom) < TOL) {
			// parallel or collinear: treat as no single intersection
			return Pos{-1, -1, -1.0, -1.0};
		}
		// solve for t,u where P = s + t*(e-s) = o.s + u*(o.e-o.s)
		double dx3 = x3 - x1, dy3 = y3 - y1;
		double t = cross(dx3, dy3, dx2, dy2) / denom;
		double u = cross(dx3, dy3, dx1, dy1) / denom;
		if (t < -TOL || t > 1 + TOL || u < -TOL || u > 1 + TOL) {
			return Pos{-1, -1, -1.0, -1.0};
		}
		double ix = x1 + t * dx1;
		double iy = y1 + t * dy1;
		return Pos{-1, -1, ix, iy};
	}
};

struct Circle {
	Pos c;
	double r;
	std::vector<Pos> intersect_at(const Segment& seg) const {
		std::vector<Pos> intersections;
		// Compute intersection(s) between circle centered at c with radius r and segment seg
		// Parametrize segment: P(t) = seg.s + t*(seg.e - seg.s), t in [0,1]
		double x1 = seg.s.x - c.x;
		double y1 = seg.s.y - c.y;
		double dx = seg.e.x - seg.s.x;
		double dy = seg.e.y - seg.s.y;
		// We rewrite as (x1 + t*dx)^2 + (y1 + t*dy)^2 = r^2
		double A = dx*dx + dy*dy;
		double B = 2*(x1*dx + y1*dy);
		double C = x1*x1 + y1*y1 - r*r;
		double disc = B*B - 4*A*C;
		if (A < TOL) {
			// segment is a point
			if (std::abs(C) < TOL) {
				intersections.push_back(Pos{-1, -1, seg.s.x, seg.s.y});
			}
			return intersections;
		}
		if (disc < -TOL) return intersections;
		if (disc < 0) disc = 0;
		double sqrtD = std::sqrt(disc);
		double t1 = (-B - sqrtD) / (2*A);
		double t2 = (-B + sqrtD) / (2*A);
		auto push_if_in_seg = [&](double t) {
			if (t >= -TOL && t <= 1 + TOL) {
				double ix = seg.s.x + t*dx;
				double iy = seg.s.y + t*dy;
				intersections.push_back(Pos{-1, -1, ix, iy});
			}
		};
		push_if_in_seg(t1);
		// avoid duplicate when disc == 0 (t1==t2)
		if (std::abs(t2 - t1) > TOL) push_if_in_seg(t2);
		return intersections;
	}
};

std::vector<std::vector<Pos>> points;
int q_id[1000 * 1000 * 8];

struct Edge {
	int v;
	double weight;
};

std::vector<double> dijkstra(
	int q,
	const std::vector<int>& start_group, 
	const std::vector<std::vector<Edge>>& graph) {
	std::vector<double> dist(cnt, 1e9);
	std::vector<double> answers(q, 1e9);
	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
	for (int start : start_group) {
		dist[start] = 0;
		pq.push({0, start});
	}
	while (!pq.empty()) {
		auto e = pq.top();
		double d = e.first;
		int u = e.second;
		pq.pop();
		if (d > dist[u]) continue;
		if (q_id[u] != -1 && dist[u] < answers[q_id[u]]) answers[q_id[u]] = dist[u];
		for (const auto& e: graph[u]) {
			if (dist[e.v] > dist[u] + e.weight) {
				dist[e.v] = dist[u] + e.weight;
				pq.push({dist[e.v], e.v});
			}
		}
	}
	return answers;
}

void solve() {
	int N, Q;
	double R;
	std::cin >> N >> R;
	std::vector<Segment> segments(N);
	std::vector<Pos> pos;
	points.resize(N);
	for (int i = 0; i < N; ++i) points[i].clear();
	memset(q_id, -1, sizeof q_id);
	std::vector<std::vector<Edge>> graph;
	std::vector<int> start_group;
	cnt = 0;
	
	for (int i = 0; i < N; ++i) {
		int m;
		double c;
		std::cin >> segments[i].s.x >> segments[i].s.y >> segments[i].e.x >> segments[i].e.y;
		std::cin >> m;
		for (int j = 0; j < m; ++j) {
			std::cin >> c;
			Pos target = {cnt++, -1,
				segments[i].s.x + (segments[i].e.x - segments[i].s.x) * c,
				segments[i].s.y + (segments[i].e.y - segments[i].s.y) * c};
			pos.push_back(target);
			points[i].push_back(target);
			start_group.push_back(target.id);
		}
		for (int j = 0; j < i; ++j) {
			auto inters = segments[i].intersect_at(segments[j]);
			if (inters.x != -1 && inters.y != -1) {
				Pos new_p = {cnt++, -1, inters.x, inters.y};
				points[i].push_back(new_p);
				points[j].push_back(new_p);
				pos.push_back(new_p);
			}
		}
	}
	std::cin >> Q;
	std::vector<Circle> circles(Q);
	for (int i = 0; i < Q; ++i) {
		std::cin >> circles[i].c.x >> circles[i].c.y;
		circles[i].r = R;
		for (const int start : start_group) {
			double dist = std::hypot(circles[i].c.x - pos[start].x,
			                         circles[i].c.y - pos[start].y);
			if (dist <= R + TOL) {
				// answer is zero
				circles[i].r = -1e9;
			}
		}
		if (circles[i].r < -1) {
			// no need to process intersections
			continue;
		}
		for (int j = 0; j < N; ++j) {
			const auto& seg = segments[j];
			auto inters = circles[i].intersect_at(seg);
			for (const auto& p : inters) {
				Pos new_p = p;
				q_id[cnt] = i;
				new_p.id = cnt++;
				new_p.q_id = i;
				points[j].push_back(new_p);
				pos.push_back(new_p);
			}
		}
		
	}
	graph.resize(cnt);
	for (int i = 0; i < N; ++i) {
		std::sort(points[i].begin(), points[i].end());
		for (size_t j = 1; j < points[i].size(); ++j) {
			double dist = std::hypot(points[i][j].x - points[i][j - 1].x,
			                         points[i][j].y - points[i][j - 1].y);
			graph[points[i][j - 1].id].push_back({points[i][j].id, dist});
			graph[points[i][j].id].push_back({points[i][j - 1].id, dist});
		}
	}
	auto answers = dijkstra(Q, start_group, graph);
	for (int i = 0; i < Q; ++i) {
		if (circles[i].r < -1) {
			answers[i] = 0.0;
		}
	}
	for (const auto& ans : answers) {
		if (ans < 1e9) {
			std::cout << ans << "\n";
		} else {
			std::cout << "-1\n";
		}
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	(std::cout << std::fixed).precision(9);
	int t;
	std::cin >> t;
	while (t--) solve();
	return 0;
}