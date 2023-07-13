template <typename E>
struct ActedMonoid_MinMax_Add {
    using Monoid_X = Monoid_MinMax<E>;
    using Monoid_A = Monoid_Add<E>;
    using X = typename Monoid_X::value_type;
    using A = typename Monoid_A::value_type;
    static constexpr X act(const X &x, const A &a, const long long &size) {
        E lo = (x.first == inf<E> ? x.first : x.first + a);
        E hi = (x.second == -inf<E> ? x.second : x.second + a);
        return {lo, hi};
    }
};
