#pragma once
#include "bits/stdc++.h"
struct BasicTreeTag{};
struct _basic_tree_impl{
    using tag = BasicTreeTag;
    vector<vector<int>> t;
    int n;
    int _edges = 0;
    _basic_tree_impl(int _n) : n(_n), t(_n) {}
    void operator+=(pair<int, int> edge){
        ++_edges;
        t[edge.first].push_back(edge.second);
        t[edge.second].push_back(edge.first);
    }
    const vector<int>& operator[](int u) const {
        return t[u];
    }
    int size() const {
        return n;
    }
};
