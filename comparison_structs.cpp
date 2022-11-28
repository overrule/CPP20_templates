template<typename T, typename _cmp_type>
struct cmp_with{
    T val;
    _cmp_type cmp;
    cmp_with(_cmp_type _cmp, T _val) : val(_val), cmp(_cmp) {}
    bool operator()(const T& x) const{
        return cmp(x, val);
    }
};
template<typename T>
inline auto less_than(T val){
    return cmp_with(std::less<T>(), val);
}
template<typename T>
inline auto greater_than(T val){
    return cmp_with(std::greater<T>(), val);
}
template<typename T>
inline auto less_equal_to(T val){
    return cmp_with(std::less_equal<T>(), val);
}
template<typename T>
inline auto greater_equal_to(T val){
    return cmp_with(std::greater_equal<T>(), val);
}
template<typename T>
inline auto is_equal_to(T val){
    return cmp_with(std::equal_to<T>(), val);
}
template<typename T>
inline auto is_not_equal_to(T val){
    return cmp_with(std::not_equal_to<T>(), val);
}
