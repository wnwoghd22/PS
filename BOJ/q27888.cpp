#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>

const int LEN = 5e5;
std::map<std::string, int> name_map, feature_map;
int N, R, feature_count;
int get_feature(char* s) {
    std::string buffer = "";
    int result = 0;

    for (int i = 0; s[i]; ++i) {
        if (s[i] == ',') {
            // std::cout << buffer << ' ';
            if (feature_map.find(buffer) == feature_map.end())
                feature_map[buffer] = feature_count++;
            result |= 1 << feature_map[buffer];
            buffer = "";
        }
        else buffer += s[i];
    }
    // std::cout << buffer << ' ';
    if (feature_map.find(buffer) == feature_map.end())
        feature_map[buffer] = feature_count++;
    result |= 1 << feature_map[buffer];
    // std::cout << '\n';
    return result;
}
int count[1 << 9];
int db[LEN];
std::string name;
char q, line[2000], features[1000];

int main() {
    freopen("input.txt", "r", stdin);
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> name;
        name_map[name] = i;
    }
    std::cin >> R;
    std::cin.getline(line, 2000);
    while (R--) {
        std::cin.getline(line, 2000, '\n');
        name = "";
        int j, k;
        if (line[0] == 'U') {
            for (j = 2; line[j] != ' ' && line[j] != '\n'; ++j) name += line[j];
            int n = name_map[name];
            int f = 0;
            if (line[j] == ' ')
                f = get_feature(&line[j + 1]);

            for (int i = 0; i < (1 << 9); ++i) {
                if ((i & db[n]) ^ i && (i & f) == i) ++count[i];
                if ((i & db[n]) == i && (i & f) ^ i) --count[i];
            }
            db[n] = f;
        }
        if (line[0] == 'G') {
            int f = 0;
            if (line[1] == ' ')
                f = get_feature(&line[2]);

            std::cout << count[f] << '\n';
        }
    }
}
