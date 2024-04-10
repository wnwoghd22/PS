#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	string rawFilePath = "map_100_100.txt";
	string filePath = "converted.txt";

	ifstream openFile(rawFilePath.data());
	ofstream writeFile(filePath.data());

	int lineNum = 0;
	int count = 0;
	int obstacles = 0;
	
	if (openFile.is_open()) {
		std::cout << "open" << '\n';
		char line[110];
		while (openFile.getline(line, 101)) {
			cout << line << '\n';

			if (writeFile.is_open()) {
				if (lineNum == 0 || lineNum == 99)
					writeFile << line << '\n';
				else {
					for (int i = 1; i < 99; ++i) {
						if (line[i] == '#') {
							line[i] = '.';
							count++;
						}
						if (line[i] == 'X') obstacles++;
					}
					writeFile << line << '\n';
				}
				lineNum++;
			}
		}if (writeFile.is_open()) {
			writeFile.close();
		}
		openFile.close();
	}

	cout << "vac: " << count << '\n';
	cout << "obs: " << obstacles << '\n';

	return 0;
}