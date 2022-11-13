//Input : A range with integer values
//Output : The smallest non-negative integer not contained in range
auto MEX(ranges::range auto&& rg){
    static_assert(is_integral<std::remove_reference_t<decltype(*rg.begin())>);
    int sz = ranges::size(rg);
    vector<char> exists(sz);
    for(auto &x : rg) if(x < sz && x >= 0) exists[x] = 1;
    return ranges::find(exists, 0) - exists.begin();
}
