auto MEX(ranges::viewable_range auto&& rg){
    int sz = ranges::size(rg);
    vector<char> exists(sz);
    for(auto &x : rg) if(x < sz && x >= 0) exists[x] = 1;
    return ranges::find(exists, 0) - exists.begin();
}
