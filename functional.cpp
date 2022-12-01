template<typename T>
struct is_callable_impl {
private:
    typedef char(&yes)[1];
    typedef char(&no)[2];

    struct Fallback { void operator()(); };
    struct Derived : T, Fallback { };

    template<typename U, U> struct Check;

    template<typename>
    static yes test(...);

    template<typename C>
    static no test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};
template<typename T>
struct is_callable
    : std::conditional<
        std::is_class<T>::value,
        is_callable_impl<T>,
        std::false_type
    >::type
{ };
template <typename F, typename G> auto compose(F f, G g) {
  return
      [f, g](auto &&...xs) { return g(f(std::forward<decltype(xs)>(xs)...)); };
}
template<typename F, typename G> requires is_callable<F>::value && is_callable<G>::value
auto operator|(F f, G g){
    return compose(std::forward<F>(f), std::forward<G>(g));
}
template<typename F, typename G> requires is_callable<G>::value && (not is_same_v<std::decay_t<F>, std::istream>)
auto operator>>(const F& f, G g){
    return g(std::forward<F>(f));
}
template<typename F, typename G> requires is_callable<G>::value && (not is_same_v<std::decay_t<F>, std::istream>)
auto operator>>(F&& f, G g){
    return g(std::forward<F>(f));
}
