#pragma once
#include <bits/stdc++.h>
#include "basic_tree_impl.hpp"
struct TreePullPushTag{};
template<typename TreeType> requires has_tag_v<TreeType, BasicTreeTag>  
struct tree_pull_push : TreeType {
    using tag = TreePullPushTag;
    using _TreeType = TreeType;
    using _TreeType::_edges;
    using _TreeType::n;
    tree_pull_push(int _n) : TreeType(_n) {}
    template<typename F_1, typename F_2>
    void dfs(int root, F_1&& _push, F_2&& _pull) const {
        auto _internal_dfs = [&](int u, int par, auto&& dfs) -> void {
            for(auto &v : TreeType::t[u]){
                if(v == par) continue;
                _push(u, v);
                dfs(v, u, dfs);
                _pull(u, v);
            }
        };
        _internal_dfs(root, -1, _internal_dfs);
    }
};
using TreePullPush = tree_pull_push<_basic_tree_impl<>>;
