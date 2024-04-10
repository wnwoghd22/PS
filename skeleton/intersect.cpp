const int LEN = 3001;
typedef long long ll;
struct Pos { ll x, y; } pos[LEN][2];

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}
bool intersect(Pos p1, Pos p2, Pos p3, Pos p4) {
	ll ccw1 = cross(p1, p2, p3), ccw2 = cross(p1, p2, p4);
	ll ccw3 = cross(p3, p4, p1), ccw4 = cross(p3, p4, p2);
	return ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0;
}