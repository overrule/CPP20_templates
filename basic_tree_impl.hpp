#pragma once
#include "bits/stdc++.h"
#include "tree_tag.hpp"
struct BasicTreeTag;
template<typename adjacency_list = basic_string<int>>
struct _basic_tree_impl{
    using tag = BasicTreeTag;
    vector<adjacency_list> t;
    int n;
    int _edges = 0;
    _basic_tree_impl(int _n) : n(_n), t(_n) {}
    void operator+=(pair<int, int> edge){
        ++_edges;
        t[edge.first].push_back(edge.second);
        t[edge.second].push_back(edge.first);
    }
    const auto& operator[](int u) const {
        return t[u];
    }
    int size() const {
        return n;
    }
};
