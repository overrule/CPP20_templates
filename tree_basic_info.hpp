#include "tree_pull_push.hpp"
struct TreeBasicInfoTag{};
template<typename TreeType> requires has_tag_v<TreeType, TreePullPushTag>
struct tree_basic_info : TreeType {
    using tag = TreeBasicInfoTag;
    using _TreeType = TreeType;
    using _TreeType::_edges;
    using _TreeType::n;

    vector<int> _subtree_sizes, _parent_of, _depth_of;
    int root = 0;
    tree_basic_info(int _n, int _root = 0) : TreeType(_n), root(_root), _subtree_sizes(_n, 1), _parent_of(_n), _depth_of(_n) {}
    auto precomp_pull(){
        return [&](int u, int v){
            _subtree_sizes[u] += _subtree_sizes[v];
            if constexpr (has_precomp_pull_v<TreeType>) {
                TreeType::precomp_pull()(u, v);
            }
        };
    }
    auto precomp_push(){
        return [&](int u, int v){
            _parent_of[v] = u;
            _depth_of[v] = _depth_of[u] + 1;
            if constexpr (has_precomp_push_v<TreeType>) {
                TreeType::precomp_push()(u, v);
            }
        };
    }
    void operator+=(pair<int, int> edge){
        TreeType::operator+=(edge);
        if(this->_edges == n - 1) TreeType::dfs(root, precomp_push(), precomp_pull());
    }
};
