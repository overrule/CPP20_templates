enum SearchType{
    first_false,
    last_true
};
#define _st_search
template<typename T, typename F_m>
struct segment_tree {
    int n;
    int n__;
    vector<T> st;
    F_m join;
    T base = T();
    segment_tree(ranges::range auto&& r, F_m _join, T _base = T()) : n__(std::distance(r.begin(), r.end())), join(_join), base(_base){
        #ifdef _st_search
        n = 1 << (32 - __builtin_clz(n__ - 1));
        #else
        n = n__;
        #endif
        st.resize(n << 1);
        for(int i=0; auto x : r){
            st[n + i] = x;
            ++i;
        }
        for(int i=n__;i<n;i++) st[n + i] = base;
        build();
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            st[i] = join(st[(i << 1)], st[(i << 1) | 1]);
        }
    }
    segment_tree(const ranges::range auto& r, F_m join, T base = T()) : n__(std::distance(r.begin(), r.end())), join(join), base(base){
        #ifdef _st_search
        n = 1 << (32 - __builtin_clz(n__ - 1));
        #else
        n = n__;
        #endif
        st.resize(n << 1, base);
        for(int i=0; auto x : r){
            st[n + i] = x;
            ++i;
        }
        for(int i=n__;i<n;i++) st[n + i] = base;
        build();
    }
    void calc(int pos){
        pos >>= 1;
        while (pos) {
            st[pos] = join(st[pos << 1], st[(pos << 1) | 1]);
            pos >>= 1;
        }
    }
    void set(int pos, T val){
        pos += n;
        st[pos] = val;
        calc(pos);
    }
    auto set__(){
        return [&](int pos, T val){
            return set(pos, val);
        };
    }
    void increment(int pos, T val){
        pos += n;
        st[pos] = join(st[pos], val);
        calc(pos);
    }
    auto increment__(){
        return [&](int pos, T val){
            return increment(pos, val);
        };
    }
    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                ansl = join(ansl, st[l++]);
            }
            if (r & 1) {
                ansr = join(st[--r], ansr);
            }
            l >>= 1;
            r >>= 1;
        }
        return join(ansl, ansr);
    }
    auto query__(){
        return [&](int l, int r){
            return query(l, r);
        };
    }
    template<typename F> requires std::is_invocable_v<F, T> and std::is_same_v<bool, decltype(declval<F>()(declval<T>()))>;
    pair<T, int> prefix_search(F cond, SearchType search_type, int start_loc = 0) {
        start_loc += n;
        int curr_idx = start_loc;
        T curr_val = base;
        curr_idx >>= __builtin_ctz(curr_idx);
        while(__builtin_popcount(curr_idx + 1) != 1){
            auto nxt = join(curr_val, st[curr_idx]);
            if(!cond(nxt)) break;
            curr_idx >>= 1;
            curr_idx += 1;
            curr_val = nxt;
            curr_idx >>= __builtin_ctz(curr_idx);
        }
        while(curr_idx < n){
            curr_idx <<= 1;
            T merged = join(curr_val, st[curr_idx]);
            if(cond(merged)){
                curr_val = merged;
                curr_idx++;
            }
        }
        if(auto merged = join(curr_val, st[curr_idx]); cond(merged)){
            curr_val = merged;
            curr_idx++;
        }
        if(search_type == SearchType::last_true){
            return pair(min(curr_idx - n - 1, n__ - 1), curr_val);
        }
        else{
            return pair(min(curr_idx - n, n__), join(curr_val, st[curr_idx]));
        }
    }
    template<typename F> // requires std::is_invocable_v<F, T> and std::is_same_v<bool, decltype(declval<F>()(declval<T>()))>;
    pair<T, int> suffix_search(F cond, SearchType search_type, int start_loc = -1) {
        if(start_loc == -1) start_loc = n__ - 1;
        start_loc += n;
        int curr_idx = start_loc;
        T curr_val = base;
        curr_idx >>= __builtin_ctz(~curr_idx);
        while(__builtin_popcount(curr_idx) != 1){
            auto nxt = join(st[curr_idx], curr_val);
            if(!cond(nxt)) break;
            curr_idx >>= 1;
            curr_idx -= 1;
            curr_val = nxt;
            curr_idx >>= __builtin_ctz(~curr_idx);
        }
        while(curr_idx < n){
            curr_idx <<= 1;
            curr_idx++;
            T merged = join(curr_val, st[curr_idx]);
            if(cond(merged)){
                curr_val = merged;
                curr_idx--;
            }
        }
        if(auto merged = join(st[curr_idx], curr_val); cond(merged)){
            curr_val = merged;
            --curr_idx;
        }
        if(search_type == SearchType::last_true){
            return pair(curr_idx - n + 1, curr_val);
        }
        else{
            return pair(curr_idx - n, join(curr_val, st[curr_idx]));
        }
    }
};
#undef _st_search
