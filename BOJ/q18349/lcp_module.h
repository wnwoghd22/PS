#ifndef __LCP_MODULE__
#define __LCP_MODULE__

#include <vector>
#include <string>
#include <algorithm>

struct SparseTable {
    int n;
    std::vector<int> lg;
    std::vector<std::vector<int>> st;
    SparseTable() : n(0) {}
    SparseTable(const std::vector<int>& a) { build(a); }
    void build(const std::vector<int>& a);
    int query(int l, int r) const;
};

void preprocess(const std::vector<std::string>&);

/// <summary>
/// find cost between node i and j
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
int C(int i, int j);
#endif
