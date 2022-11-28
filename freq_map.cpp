namespace std::ranges{

template<ranges::range R>
auto _freq_map(R&& r){
    using T = std::remove_decay_t<decltype(*r.begin())>;
    std::map<T, int> __freq_map;
    auto iter_rg = r.begin();
    while(iter_rg != r.end()){
        __freq_map[*iter_rg]++;
        iter_rg++;
    }
    return __freq_map; 
}
struct freq_map_range_adapter{
    template<ranges::range R>
    constexpr auto operator()(R&& r) const{
        return _freq_map(std::forward<R>(r));
    }
};
template <ranges::range R>
constexpr auto operator | (R&& r, const freq_map_range_adapter& adapter){
    return adapter(std::forward<R>(r));
}
//Returns std::map<T, int>, where map[x] returns the number of times x exists in the input range
freq_map_range_adapter freq_map;
}
