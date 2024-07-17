template<typename T, typename F_m> 
struct segment_tree {
    int n;
    int n__;
    vector<T> st;
    F_m join;
    T base = T();
    segment_tree(ranges::input_range auto&& r, F_m _join, T _base = T()) : n__(std::distance(r.begin(), r.end())), join(_join), base(_base){
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
        st.resize(n << 1);
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
    void increment(int pos, T val){
        pos += n;
        st[pos] = join(st[pos], val);
        calc(pos);
    }
    class Proxy {
        segment_tree& seg_tree;
        int pos;
    public:
        Proxy(segment_tree& st, int p) : seg_tree(st), pos(p) {}
        Proxy& operator=(T val) {
            seg_tree.set(pos, val);
            return *this;
        }
        Proxy& operator*=(T val) {
            seg_tree.increment(pos, val);
            return *this;
        }
        operator T() const {
            return seg_tree.st[pos + seg_tree.n];
        }
    };
    Proxy operator[](int pos) {
        return Proxy(*this, pos);
    }
    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n+1;
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
    T operator()(int l, int r) {
    	return query(l,r);
    }
    T get(int pos) {
    	if (pos<0 || pos>=n__) return base;
    	return st[pos+n];
    }
    template<typename F>
    pair<T,int> prefix_search(F cond, int start_loc = 0) {
    	start_loc++;
        if (start_loc == 0) return pair(-1,base);
        int curr_idx = start_loc + n;
        T curr_val = base;
        do {
            curr_idx--;
            while (curr_idx > 1 && (curr_idx % 2)) curr_idx >>= 1;
            if (!cond(join(st[curr_idx], curr_val))) {
                while (curr_idx < n) {
                    curr_idx <<= 1;
                    curr_idx++;
                    if (cond(join(st[curr_idx], curr_val))) {
                        curr_val = join(st[curr_idx], curr_val);
                        curr_idx--;
                    }
                }
                return pair(curr_idx - n,st[curr_idx]);
            }
            curr_val = join(st[curr_idx], curr_val);
        } while ((curr_idx & -curr_idx) != curr_idx);
        return pair(-1,base);
    }
    template<typename F>
    pair<T,int> suffix_search(F cond, int start_loc = -1) {
        if (start_loc == n__) return pair(n__,base);
        int curr_idx = start_loc + n;
        T curr_val = base;
        do {
            while (curr_idx % 2 == 0) curr_idx >>= 1;
            if (!cond(join(curr_val, st[curr_idx]))) {
                while (curr_idx < n) {
                    curr_idx <<= 1;
                    if (cond(join(curr_val, st[curr_idx]))) {
                        curr_val = join(curr_val, st[curr_idx]);
                        curr_idx++;
                    }
                }
                return pair(curr_idx - n,st[curr_idx]);
            }
            curr_val = join(curr_val, st[curr_idx]);
            curr_idx++;
        } while ((curr_idx & -curr_idx) != curr_idx);
        return pair(n__,base);
    }
};
