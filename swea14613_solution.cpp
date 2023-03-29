#include <map>
#include <string>

enum Type {
	ORIGINAL,
	SHALLOW,
	DEEP,
};

const int M_LEN = 200'001;
const int N_LEN = 5010;
const int U_LEN = 100'000;

struct Snapshot {
	int v;
	int time_stamp;
	int next;
	Snapshot() : v(-1), time_stamp(-1), next(-1) {}
} snapshots[U_LEN];
int update_order;

int origin_order;
int A[10][M_LEN];
int order;
std::map<std::string, int> order_map;
int types[N_LEN];
int link[N_LEN]; // array index or parent
int stamp[N_LEN];
std::map<int, int> update_map[N_LEN];
std::map<int, int> update_head[N_LEN];

void init()
{
	update_order = origin_order = order = 0;
	order_map.clear();
	for (std::map<int, int>& m : update_map) m.clear();
	for (std::map<int, int>& m : update_head) m.clear();
	for (int i = 0; i < U_LEN; ++i) snapshots[i] = Snapshot();
}

void makeList(char mName[], int mLength, int mListValue[])
{
	std::string name(mName);
	int o = order_map[name] = order++;
	types[o] = ORIGINAL;
	int k = link[o] = origin_order++;
	for (int i = 0; i < mLength; ++i)
		A[k][i] = mListValue[i];
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
	std::string dest(mDest), src(mSrc);
	int src_o = order_map[src];
	if (types[src_o] == SHALLOW)
		src_o = link[src_o];
	int dest_o = order_map[dest] = order++;
	types[dest_o] = mCopy ? DEEP : SHALLOW;
	link[dest_o] = src_o;
	stamp[dest_o] = update_order;
}

void updateElement(char mName[], int mIndex, int mValue)
{
	std::string name(mName);
	int o = order_map[name];
	if (types[o] == SHALLOW)
		o = link[o];
	if (update_map[o].find(mIndex) != update_map[o].end()) {
		// int s = update_map[o][mIndex];
		// while (~snapshots[s].next) s = snapshots[s].next;
		int s = update_head[o][mIndex];
		snapshots[s].next = update_order;
	}
	else update_map[o][mIndex] = update_order;
	snapshots[update_order].v = mValue;
	update_head[o][mIndex] = update_order;
	snapshots[update_order].time_stamp = update_order++;
}

int element(char mName[], int mIndex)
{
	int result = -1;
	std::string name(mName);
	int o = order_map[name];
	if (types[o] == SHALLOW)
		o = link[o];
	int bound_t = update_order;
	while (1) {
		if (update_map[o].find(mIndex) != update_map[o].end()) {
			int s = update_map[o][mIndex];
			while (1) {
				Snapshot sn = snapshots[s];
				if (sn.time_stamp >= bound_t) break;
				result = sn.v;
				if (~sn.next) s = sn.next;
				else break;
			}
			if (~result) return result;
		}
		if (types[o] == ORIGINAL) break; // no snapshots
		else bound_t = stamp[o], o = link[o]; // search parent
	}
	result = A[link[o]][mIndex];
	return result;
}