namespace std::ranges{

template<ranges::range R, typename T>
auto _prefix_fold(R r, auto&& f, T initial){
    vector<T> __prefix_fold;
    __prefix_fold.resize(ranges::size(r) + 1);
    __prefix_fold[0] = initial;
    auto iter_rg = r.begin();
    auto iter_fold = __prefix_fold.begin();
    while(iter_rg != r.end()){
        *(++iter_fold) = f(*iter_fold, *iter_rg);
        ++iter_rg;
    }
    return __prefix_fold; 
}
template<typename T, typename F>
struct prefix_fold_range_adapter_closure{
    T initial;
    F f;
    template<ranges::viewable_range R>
    constexpr auto operator()(R&& r){
        return _prefix_fold<ranges::views::all_t<R>, T>(r, std::move(f), initial);
    }
    prefix_fold_range_adapter_closure(F&& _f, T _initial) : f(_f), initial(_initial) {}
};
struct prefix_fold_range_adapter{
    template<ranges::viewable_range R>
    constexpr auto operator()(R&& r, auto&& f, auto initial) const{
        return _prefix_fold<ranges::views::all_t<R>, decltype(initial)>(r, std::move(f), initial);
    }
    constexpr auto operator()(auto &&f, auto initial) const{
        return prefix_fold_range_adapter_closure(std::forward<decltype(f)>(f), initial);
    }
};
template <ranges::viewable_range R, typename T, typename F>
constexpr auto operator | (R&& r, prefix_fold_range_adapter_closure<T, F>&& closure){
    return closure(std::forward<R>(r));
}
//returns std::vector<T> prefix_fold, where T is return type of lambda
//prefix_fold[0] = initial, and prefix_fold[i] = f(prefix_fold[i-1], a[i-1]), where a is input range
prefix_fold_range_adapter prefix_fold;
}
