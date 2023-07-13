template <typename T>
struct Monoid_Lcm {
    using value_type = T;
    using X = value_type;
    static X op(X x, X y) {
        if (x == inf<T> || y == inf<T>) return inf<T>;
        x /= gcd(x, y);
        if (x >= ceil(inf<T>, y)) return inf<T>;
        return x * y;
    }
    static constexpr X unit() { return 1; }
    static constexpr bool commute = true;
};
