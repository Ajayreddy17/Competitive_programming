//requires Monoid_Add
//requires Monoid_Mul

template<typename E>
struct ActedMonoid_Add_Mul {
    using Monoid_X = Monoid_Add<E>;
    using Monoid_A = Monoid_Mul<E>;
    using X = typename Monoid_X::value_type;
    using A = typename Monoid_A::value_type;

    static constexpr X act(const X &x, const A &a, const long long &size = 1) {
        return x * a;
    }
};
