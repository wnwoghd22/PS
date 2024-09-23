#include <iostream>

bool check[26];

int main() {
	std::string wheel, target;
	int wheel_len, len;

	std::cin >> wheel_len;
	std::cin >> wheel;
	for (const char& c : wheel) check[c - 'a'] = true;

	std::cin >> len;
	std::cin >> target;

	bool flag = true;
	for (const char& c : target) if (!check[c - 'a']) flag = false;

	if (!flag) {
		std::cout << -1;
	}
	else {
		int rotate = 0;
		int index = wheel_len - 1;
		for (const char& c : target) {
			 do {
				++rotate;
				++index;
				if (index == wheel_len) index = 0;
			} while (wheel[index] != c);
		}
		std::cout << rotate;
	}
}