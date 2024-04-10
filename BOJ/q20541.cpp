#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>

const int LEN = 1e5 + 1;

std::string dir_name[LEN];
std::map<std::string, int> subdir[LEN];
int dirs, par[LEN];
std::set<std::string> pic[LEN];

int wd; // working dir

void mkalb(int dir, const std::string& s) {
	if (subdir[dir].find(s) != subdir[dir].end()) {
		std::cout << "duplicated album name\n";
		return;
	}
	++dirs;
	dir_name[dirs] = s;
	subdir[dir][s] = dirs;
	par[dirs] = dir;
}

void dfs(int u, int& dirs, int& files) {
	++dirs;
	files += pic[u].size();
	for (const auto&[k, v] : subdir[u])
		dfs(v, dirs, files);
}

void rmalb(int dir, const std::string& s) {
	int dirs = 0, files = 0;
	if (subdir[dir].size()) {
		if (s == "-1") {
			std::string first = (*(subdir[dir].begin())).first;
			dfs(subdir[dir][first], dirs, files);
			subdir[dir].erase(first);
		}
		else if (s == "0") {
			for (const auto&[k, v] : subdir[dir]) dfs(v, dirs, files);
			subdir[dir].clear();
		}
		else if (s == "1") {
			std::string last = (*(std::prev(subdir[dir].end()))).first;
			dfs(subdir[dir][last], dirs, files);
			subdir[dir].erase(last);
		}
		else {
			if (subdir[dir].find(s) != subdir[dir].end()) {
				dfs(subdir[dir][s], dirs, files);
				subdir[dir].erase(s);
			}
		}
	}
	std::cout << dirs << ' ' << files << '\n';
}

void insert(int dir, const std::string& s) {
	if (pic[dir].find(s) != pic[dir].end()) {
		std::cout << "duplicated photo name\n";
		return;
	}
	pic[dir].insert(s);
}

void erase(int dir, const std::string& s) {
	int files = 0;
	if (pic[dir].size()) {
		if (s == "-1") {
			std::string first = (*(pic[dir].begin()));
			pic[dir].erase(first);
			files = 1;
		}
		else if (s == "0") {
			files = pic[dir].size();
			pic[dir].clear();
		}
		else if (s == "1") {
			std::string last = (*std::prev((pic[dir].end())));
			pic[dir].erase(last);
			files = 1;
		}
		else {
			if (pic[dir].find(s) != pic[dir].end()) {
				pic[dir].erase(s);
				files = 1;
			}
		}
	}
	std::cout << files << '\n';
}

void ca(std::string& s) {
	if (s == "..") wd = par[wd];
	else if (s == "/") wd = 0;
	else {
		if (subdir[wd].find(s) != subdir[wd].end()) 
			wd = subdir[wd][s];
	}
	std::cout << dir_name[wd] << '\n';
}

int N;
std::string args[2];

int main() {
	freopen("input.txt", "r", stdin);

	dir_name[0] = "album";

	std::cin >> N;
	while (N--) {
		std::cin >> args[0] >> args[1];
		if (args[0] == "mkalb") mkalb(wd, args[1]);
		if (args[0] == "rmalb") rmalb(wd, args[1]);
		if (args[0] == "insert") insert(wd, args[1]);
		if (args[0] == "delete") erase(wd, args[1]);
		if (args[0] == "ca") ca(args[1]);
	}
}