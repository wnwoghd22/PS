#include <iostream>

int main() {
    (std::cout << std::fixed).precision(2);
    while (1) {
        long double w;
        std::cin >> w;
        if (w < 0) break;
        std::cout << "Objects weighing " << w << " on Earth will weigh " << 0.167 * w << " on the moon.\n";
    }
}