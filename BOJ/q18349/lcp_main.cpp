#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#include "lcp_module.h"

std::vector<std::string> data;

int main() {
    // generate random lowercase strings using only 'a' and 'b'
    const int N = 200; // number of strings to test
    const int MAX_LEN = 20;

    std::mt19937_64 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    // ensure generated strings have at least one character
    std::uniform_int_distribution<int> len_dist(1, MAX_LEN);
    // only 'a' and 'b'
    std::uniform_int_distribution<int> char_dist(0, 1);
    std::bernoulli_distribution copy_prefix(0.5); // 50% chance to copy a prefix from an earlier string

    data.reserve(N);
    for (int i = 0; i < N; ++i) {
        int L = len_dist(rng);
        std::string s;
        s.reserve(L);

        if (i > 0 && copy_prefix(rng)) {
            // pick a random earlier string and copy a random-length prefix to boost common substrings
            std::uniform_int_distribution<int> pick_prev(0, i - 1);
            int src = pick_prev(rng);
            if (!data[src].empty()) {
                int max_pref = std::min((int)data[src].size(), L);
                std::uniform_int_distribution<int> pref_len_dist(1, max_pref);
                int pref = pref_len_dist(rng);
                s = data[src].substr(0, pref);
            }
        }

        // fill remaining characters (if any) with random 'a' or 'b'
        while ((int)s.size() < L) s.push_back('a' + char_dist(rng));
        data.push_back(std::move(s));
    }

    // also add some deterministic cases that often break implementations
	// data.push_back("");
    data.push_back("a");
    data.push_back("aa");
    data.push_back("ababa");
    data.push_back("ababab");
    data.push_back("zzzzzzzzzz");

    std::cout << "preprocess start, strings=" << data.size() << "\n";
    preprocess(data);
    std::cout << "preprocess done\n";

    bool ok = true;
    std::ofstream out; // for counterexample

    for (int i = 0; i < (int)data.size(); ++i) {
        for (int j = i + 1; j < (int)data.size(); ++j) {
            int naive = C(data[i], data[j]);
            int answer = C(i, j);

            if (naive != answer) {
                ok = false;
                std::cout << "Mismatch for (" << i << "," << j << "): naive=" << naive << " opt=" << answer << "\n";
                if (!out.is_open()) {
                    out.open("counterexample.txt");
                    out << "# Generated test data for lcp_module discrepancy\n";
                    out << "N=" << data.size() << "\n";
                    for (size_t k = 0; k < data.size(); ++k) {
                        out << k << ':' << data[k] << '\n';
                    }
                    out << "# Mismatch pairs follow\n";
                }
                out << "pair: " << i << ' ' << j << '\n';
                out << "naive: " << naive << " opt: " << answer << "\n";
                out << "string_i: " << data[i] << "\n";
                out << "string_j: " << data[j] << "\n";
                // flush so we can inspect file even if program aborts
                out.flush();
            }
        }
    }

    if (ok) std::cout << "All pairs matched.\n";
    else std::cout << "Found mismatches. See counterexample.txt\n";

    if (out.is_open()) out.close();
    return 0;
}