namespace std::ranges::views{

template<ranges::range R, typename T> requires ranges::view<R> 
struct prefix_fold_view{
    vector<T> __prefix_fold;
    prefix_fold_view(R base, auto&& f, T initial){
        __prefix_fold.resize(ranges::size(base) + 1);
        __prefix_fold[0] = initial;
        auto iter_rg = base.begin();
        auto iter_fold = __prefix_fold.begin();
        while(iter_rg != base.end()){
            *(++iter_fold) = f(*iter_fold, *iter_rg);
            ++iter_rg;
        }
    }
    auto begin(){
        return __prefix_fold.cbegin();
    }
    auto end(){
        return __prefix_fold.cend();
    }
    const int& operator[](int x){
        return __prefix_fold[x];
    }
};
template<typename T, typename F>
struct prefix_fold_range_adapter_closure{
    T initial;
    F f;
    template<ranges::viewable_range R>
    constexpr auto operator()(R&& r){
        return prefix_fold_view<ranges::views::all_t<R>, T>(r, std::move(f), initial);
    }
    prefix_fold_range_adapter_closure(F&& _f, T _initial) : f(_f), initial(_initial) {}
};
struct prefix_fold_range_adapter{
    template<ranges::viewable_range R>
    constexpr auto operator()(R&& r, auto&& f, auto initial) const{
        return prefix_fold_view<ranges::views::all_t<R>, decltype(initial)>(r, std::move(f), initial);
    }
    constexpr auto operator()(auto &&f, auto initial) const{
        return prefix_fold_range_adapter_closure(std::forward<decltype(f)>(f), initial);
    }
};
template <ranges::viewable_range R, typename T, typename F>
constexpr auto operator | (R&& r, prefix_fold_range_adapter_closure<T, F>&& closure){
    return closure(std::forward<R>(r));
}
prefix_fold_range_adapter prefix_fold;
}
