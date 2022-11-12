template<typename T, typename F>
struct segment_tree {
    int n;
    vector<T> segtree;
    F join;
    T base = T();
    segment_tree(ranges::viewable_range auto&& rg, F join, T base = T()) : n(ranges::size(rg)), join(join), base(base){
        for(int i=n; auto &x : rg) segtree[i++] = x;
        build();
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
        }
    }
    void calc(int pos){
        pos >>= 1;
        while (pos) {
            segtree[pos] = join(segtree[pos << 1], segtree[(pos << 1) | 1]);
            pos >>= 1;
        }
    }
    void set(int pos, T val){
        pos+=n;
        segtree[pos] = val;
        calc(pos);
    }
    void increment(int pos, T val){
        pos+=n;
        segtree[pos] = join(segtree[pos], val);
        calc(pos);
    }
    T operator()(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                ansl = join(ansl, segtree[l++]);
            }
            if (r & 1) {
                ansr = join(segtree[--r], ansr);
            }
            l >>= 1;
            r >>= 1;
        }
        return join(ansl, ansr);
    }
    //TODO
    /*
    T prefix_search(auto cond, int start = 0){
        T curr = base;
        int idx = n + start;
        auto find_within = [&](int idx){

        };
        auto find_subtree = [&](int idx){
            while(is_valid(idx)){
                if(idx % 2){
                    curr = join(curr, segtree[idx++]);
                }
                idx >>= 1;
            }

        };
        return find_within(find_subtree(idx)) - n;
    }
    T suffix_search(auto cond, int start = n-1){

    }
    */
};
