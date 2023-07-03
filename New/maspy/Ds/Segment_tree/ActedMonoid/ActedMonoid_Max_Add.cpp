// requires Monoid_Max
// requires Monoid_Add

template<typename E>
struct ActedMonoid_Max_Add {
    using Monoid_X = Monoid_Max<E>;
    using Monoid_A = Monoid_Add<E>;
    using X = typename Monoid_X::value_type;
    using A = typename Monoid_A::value_type;

    static constexpr X act(const X &x, const A &a, const long long &size) {
        if (x == numeric_limits<E>::min()) return x;
        return x + a;
    }
};
