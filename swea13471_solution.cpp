#include <queue>
#include <map>
#include <cstring>
#include <iostream>

const int QUERY_COUNT = 20'000;
const int LINE_COUNT = 500;

struct Task {
	int id;
	int t_stamp;
	int e_id;
	int time;
	bool processing;
	Task(int id, int t_stamp, int e_id, int time) : id(id), t_stamp(t_stamp), e_id(e_id), time(time), processing(0) { }
};

int l, m;
std::queue<Task> lines[LINE_COUNT];
int assigned_line[LINE_COUNT]; // assigned line of equipment
int release_time[LINE_COUNT]; // equipment release time

std::map<int, int> status_map;

std::priority_queue<int> stamp;
int processed_time;

void process(int time) {
	while (stamp.size() && -stamp.top() <= time) {
		int cur = -stamp.top(); stamp.pop();
		if (cur <= processed_time) continue;
		processed_time = cur;
		// std::cout << "update process: " << cur << '\n';
		for (int i = 0; i < m; ++i) {
			if (~assigned_line[i] && release_time[i] <= processed_time) {
				// std::cout << "release: " << cur << ' ' << i << ' ' << assigned_line[i] << '\n';
				lines[assigned_line[i]].pop();
				assigned_line[i] = -1;
			}
		}
		for (int i = 0; i < l; ++i) {
			if (lines[i].empty()) continue;
			if (lines[i].front().t_stamp <= processed_time && !~assigned_line[lines[i].front().e_id]) {
				// std::cout << "assign: " << cur << " ~ " << cur + lines[i].front().time << ' ' << i << ' ' << lines[i].front().id << ' ' << lines[i].front().e_id << '\n';
				assigned_line[lines[i].front().e_id] = i;
				release_time[lines[i].front().e_id] = cur + lines[i].front().time;
				lines[i].front().processing = 1;
				status_map[lines[i].front().id] = cur + lines[i].front().time;
				stamp.push(-cur - lines[i].front().time);
			}
		}
	}
}

void init(int L, int M) {
	l = L, m = M;
	for (int i = 0; i < m; ++i) assigned_line[i] = release_time[i] = -1;
	for (int i = 0; i < l; ++i) lines[i] = std::queue<Task>();
	status_map.clear();
	stamp = std::priority_queue<int>();
	processed_time = 0;
}

int request(int tStamp, int pId, int mLine, int eId, int mTime) {
	Task t(pId, tStamp, eId, mTime);
	lines[mLine].push(t);
	status_map[pId] = -1;
	stamp.push(-tStamp);
	process(tStamp);

	// std::cout << "request: " << tStamp << ' ' << mLine << ' ' << lines[mLine].front().id << ' ' << lines[mLine].front().processing << '\n';
	if (lines[mLine].front().processing) return lines[mLine].front().id;
	return -1;
}

int status(int tStamp, int pId) {
	process(tStamp);
	if (status_map.find(pId) == status_map.end())
		return 0;
	int st = status_map[pId];
	int result = st < 0 ? 1 : st > tStamp ? 2 : 3;
	// std::cout << "status: " << tStamp << ' ' << pId << ' ' << st << ' ' << result << '\n';
	if (st < 0) return 1;
	if (st > tStamp) return 2;
	return 3;
}
