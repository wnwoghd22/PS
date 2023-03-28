#include <cstring>
#include <vector>
#include <iostream>

const int U_LEN = 1001;
const int PLACE_COUNT = 50001;
const int LEN = 10000;

struct Place {
	int id;
	int r, c;
	bool is_placed;
	bool is_infected;
	Place* link[8];
	Place(int id = 0) : id(id), r(0), c(0), is_placed(0), is_infected(0) {
		for (int i = 0; i < 8; ++i)
			link[i] = 0;
	}
} places[PLACE_COUNT];

Place* row[LEN];
Place* col[LEN];
Place* ld[LEN * 2];
Place* rd[LEN * 2];

std::vector<int> visited[U_LEN];

void init()
{
	for (int i = 0; i < PLACE_COUNT; ++i) places[i] = Place(i);
	memset(col, 0, sizeof col);
	memset(row, 0, sizeof row);
	memset(ld, 0, sizeof ld);
	memset(rd, 0, sizeof rd);
	for (std::vector<int>& v : visited) v.clear();
}

void addPlace(int pID, int r, int c)
{
	places[pID].r = r;
	places[pID].c = c;
	places[pID].is_placed = 1;
	places[pID].is_infected = 0;
	for (int i = 0; i < 8; ++i) places[pID].link[i] = 0;

	if (!row[r]) row[r] = &places[pID];
	else {
		if (row[r]->c > c) {
			row[r]->link[6] = &places[pID];
			places[pID].link[2] = row[r];
			row[r] = &places[pID];
		}
		else {
			Place* now = row[r];
			while (now->link[2] && now->link[2]->c < c)
				now = now->link[2];
			if (now->link[2]) {
				now->link[2]->link[6] = &places[pID];
				places[pID].link[2] = now->link[2];
			}
			now->link[2] = &places[pID];
			places[pID].link[6] = now;
		}
	}

	if (!col[c]) col[c] = &places[pID];
	else {
		if (col[c]->r > r) {
			col[c]->link[0] = &places[pID];
			places[pID].link[4] = col[c];
			col[c] = &places[pID];
		}
		else {
			Place* now = col[c];
			while (now->link[4] && now->link[4]->r < r)
				now = now->link[4];
			if (now->link[4]) {
				now->link[4]->link[0] = &places[pID];
				places[pID].link[4] = now->link[4];
			}
			now->link[4] = &places[pID];
			places[pID].link[0] = now;
		}
	}

	int ld_i = LEN + r - c;
	if (!ld[ld_i]) ld[ld_i] = &places[pID];
	else {
		if (ld[ld_i]->r > r) {
			ld[ld_i]->link[7] = &places[pID];
			places[pID].link[3] = ld[ld_i];
			ld[ld_i] = &places[pID];
		}
		else {
			Place* now = ld[ld_i];
			while (now->link[3] && now->link[3]->r < r)
				now = now->link[3];
			if (now->link[3]) {
				now->link[3]->link[7] = &places[pID];
				places[pID].link[3] = now->link[3];
			}
			now->link[3] = &places[pID];
			places[pID].link[7] = now;
		}
	}

	int rd_i = r + c;
	if (!rd[rd_i]) rd[rd_i] = &places[pID];
	else {
		if (rd[rd_i]->r > r) {
			rd[rd_i]->link[1] = &places[pID];
			places[pID].link[5] = rd[rd_i];
			rd[rd_i] = &places[pID];
		}
		else {
			Place* now = rd[rd_i];
			while (now->link[5] && now->link[5]->r < r)
				now = now->link[5];
			if (now->link[5]) {
				now->link[5]->link[1] = &places[pID];
				places[pID].link[5] = now->link[5];
			}
			now->link[5] = &places[pID];
			places[pID].link[1] = now;
		}
	}

	// std::cout << "add place: " << pID << ' ';
	// for (int i = 0; i < 8; ++i)
	//	std::cout << (places[pID].link[i] ? places[pID].link[i]->id : -1) << ' ';
	// std::cout << '\n';
}

void removePlace(int pID)
{
	Place& p = places[pID];

	p.is_placed = 0;
	if (row[p.r] == &places[pID]) row[p.r] = p.link[2];
	if (col[p.c] == &places[pID]) col[p.c] = p.link[4];
	int ld_i = LEN + p.r - p.c; if (ld[ld_i] == &places[pID]) ld[ld_i] = p.link[3];
	int rd_i = p.r + p.c; if (rd[rd_i] == &places[pID]) rd[rd_i] = p.link[5];

	for (int i = 0; i < 8; ++i) {
		if (p.link[i])
			p.link[i]->link[(i + 4) % 8] = p.link[(i + 4) % 8];
	}
}

void contactTracing(int uID, int visitNum, int moveInfo[], int visitList[])
{
	Place* p = &places[moveInfo[0]];
	visited[uID].push_back(p->id);
	visitList[0] = p->id;
	// std::cout << "Contact tracing: " << uID << ' ' << p->id << ' ';
	for (int i = 1; i < visitNum; ++i) {
		do {
			p = p->link[moveInfo[i]];
		} while (p->is_infected);
		visited[uID].push_back(p->id);
		visitList[i] = p->id;
		// std::cout << visitList[i] << ' ';
	}
	// ::cout << '\n';
	for (const int& pID : visited[uID]) places[pID].is_infected = 1;
}

void disinfectPlaces(int uID)
{
	for (const int& pID : visited[uID]) places[pID].is_infected = 0;
	visited[uID].clear();
}